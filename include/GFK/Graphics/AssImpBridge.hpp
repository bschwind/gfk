#pragma once

#include <assimp/scene.h>
#include <GFK/Math/Matrix.hpp>

namespace gfk
{

class AssImpBridge
{
public:
	static Matrix ConvertAssImpMatrix(const aiMatrix4x4 &inMatrix);
	static void ConvertAssImpMatrix(const aiMatrix4x4 &inMatrix, Matrix &result);
};

}
