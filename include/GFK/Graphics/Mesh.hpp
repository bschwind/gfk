#pragma once

#include <GFK/Graphics/GLHeader.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Matrix.hpp>
#include <vector>
#include <string>

#if defined(PLATFORM_ANDROID)
	#include <android_native_app_glue.h>
#endif

struct aiScene;
struct aiNode;

namespace gfk
{

class Mesh
{
public:
	Mesh();
	~Mesh();
	void Bind() const;
	void Unbind() const;
	void Load(const std::string &fileName);
#if defined(PLATFORM_ANDROID)
	void Load(const std::string &fileName, android_app *app);
#endif

	int numVertices;

	struct VertexPositionColor {
		Vector3 Position;
		gfk::Color Color;
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
