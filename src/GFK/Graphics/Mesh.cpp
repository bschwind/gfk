#include <GFK/Graphics/Mesh.hpp>
#include <GFK/Graphics/AssImpBridge.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp> 
#include <assimp/postprocess.h>
#include <iostream>

namespace gfk
{

Mesh::Mesh()
{
	// Do nothing?
	name = "empty";
}

Mesh::Mesh(const std::string &fileName)
{
	name = fileName;
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName, aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_Triangulate);
	const aiNode* rootNode = scene->mRootNode;

	AddNodeRecursive(scene, rootNode, Matrix::Identity);

	numVertices = vertexBuffer.size();

#if not defined(PLATFORM_ANDROID)
	// Use a Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
#endif
	// Create a Vertex Buffer Object that will store the vertices on video memory
	glGenBuffers(1, &vbo);

	// Allocate space and upload the data from CPU to GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColor) * vertexBuffer.size(), &vertexBuffer.front(), GL_STATIC_DRAW);

	BindAttributes();

#if not defined(PLATFORM_ANDROID)
	// Bind to 0 so we don't inadvertently record any more GL operations on the VAO
	glBindVertexArray(0);
#endif
}

Mesh::~Mesh()
{
#if not defined(PLATFORM_ANDROID)
	glDeleteVertexArrays(1, &vao);
#endif
	glDeleteBuffers(1, &vbo);
}

void printAiSceneInfo(const aiScene *aiSceneP)
{
	printf("void printAiSceneInfo(const aiScene* aiSceneP)...\n");
	printf("aiSceneP->HasMeshes(): %i\n", aiSceneP->HasMeshes());

	if (aiSceneP->HasMeshes())
	{
		printf("aiScene->mNumMeshes: %i\n", aiSceneP->mNumMeshes);

		for (int i(0); i<aiSceneP->mNumMeshes; i++)
		{
			printf("aiScene->mMeshes[%i]: \n", i);

			for (int j(0); j<AI_MAX_NUMBER_OF_COLOR_SETS; j++)
			{
				printf("aiScene->mMeshes[%i]->HasVertexColors[%i]: %i\n", i, j, aiSceneP->mMeshes[i]->HasVertexColors(j));

				if (aiSceneP->mMeshes[i]->HasVertexColors(j))
				{
					for (int k(0); k < aiSceneP->mMeshes[i]->mNumVertices; k++)
					{
						printf("aiScene->mMeshes[%i]->mColors[%i][%i]: [%f, %f, %f, %f]\n",
						i,
						j,
						k,
						aiSceneP->mMeshes[i]->mColors[j][k].r,
						aiSceneP->mMeshes[i]->mColors[j][k].g,
						aiSceneP->mMeshes[i]->mColors[j][k].b,
						aiSceneP->mMeshes[i]->mColors[j][k].a);
					}
				}
				else
				{
					printf("aiScene->mMeshes[%i]->mColors[%i]: None\n", i, j);
				}
			}
		}
	}
}

void Mesh::AddNodeRecursive(const aiScene *scene, const aiNode *node, const Matrix &parentTransform)
{
	Matrix nodeTransform = AssImpBridge::ConvertAssImpMatrix(node->mTransformation);
	Matrix::Multiply(nodeTransform, parentTransform, nodeTransform);

	for (int i = 0; i < node->mNumMeshes; i++)
	{
		int meshIndex = node->mMeshes[i];
		aiMesh *mesh = scene->mMeshes[meshIndex];

		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			aiFace *face = &mesh->mFaces[j];

			for (int k = 0; k < face->mNumIndices; k++)
			{
				int vertIndex = face->mIndices[k];
				VertexPositionColor newVert;

				newVert.Position = nodeTransform * Vector3(
					mesh->mVertices[vertIndex].x,
					mesh->mVertices[vertIndex].y,
					mesh->mVertices[vertIndex].z);

				newVert.Color = Color(
					newVert.Position.X / 5,
					newVert.Position.Y / 5,
					newVert.Position.Z / 5,
					1.0f);

				vertexBuffer.push_back(newVert);
			}
		}
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		AddNodeRecursive(scene, node->mChildren[i], nodeTransform);
	}
}

void Mesh::Bind() const
{
#if not defined(PLATFORM_ANDROID)
	glBindVertexArray(vao);
#endif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	BindAttributes();
}

void Mesh::Unbind() const
{
#if not defined(PLATFORM_ANDROID)
	glBindVertexArray(0);
#endif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Mesh::BindAttributes() const
{
	int stride = sizeof(VertexPositionColor);

	// Specify how the data for position can be accessed
	glVertexAttribPointer(GLSL_ATTRIB_MAP["position"], 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(VertexPositionColor, Position));
	glVertexAttribPointer(GLSL_ATTRIB_MAP["color"], 4, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(VertexPositionColor, Color));

	// Enable the attribute
	glEnableVertexAttribArray(GLSL_ATTRIB_MAP["position"]);
	glEnableVertexAttribArray(GLSL_ATTRIB_MAP["color"]);
}

}
