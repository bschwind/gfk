#pragma once

#include <GFK/Graphics/GLHeader.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Matrix.hpp>
#include <vector>
#include <string>

struct aiScene;
struct aiNode;

namespace gfk
{

class Mesh
{
public:
	Mesh();
	Mesh(const std::string &fileName);
	~Mesh();
	void Bind() const;
	void Unbind() const;

	int numVertices;

	struct VertexPositionColor {
		Vector3 Position;
		Color Color;
	};
	
	std::vector<VertexPositionColor> vertexBuffer;
protected:
private:
	GLuint vao;
	GLuint vbo;
	std::string name;

	void AddNodeRecursive(const aiScene *scene, const aiNode *node, const Matrix &parentTransform);
	void BindAttributes() const;
};

}
