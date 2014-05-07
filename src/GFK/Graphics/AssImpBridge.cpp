#include <GFK/Graphics/AssImpBridge.hpp>

namespace gfk
{

Matrix AssImpBridge::ConvertAssImpMatrix(const aiMatrix4x4 &inMatrix)
{
	// AssImp matrices are row-major, OpenGL matrices are column-major
	return Matrix(
		inMatrix.a1, inMatrix.b1, inMatrix.c1, inMatrix.d1,
		inMatrix.a2, inMatrix.b2, inMatrix.c2, inMatrix.d2,
		inMatrix.a3, inMatrix.b3, inMatrix.c3, inMatrix.d3,
		inMatrix.a4, inMatrix.b4, inMatrix.c4, inMatrix.d4);
}

void AssImpBridge::ConvertAssImpMatrix(const aiMatrix4x4 &inMatrix, Matrix &result)
{
	result(1,1) = inMatrix.a1;
	result(1,2) = inMatrix.b1;
	result(1,3) = inMatrix.c1;
	result(1,4) = inMatrix.d1;

	result(2,1) = inMatrix.a2;
	result(2,2) = inMatrix.b2;
	result(2,3) = inMatrix.c2;
	result(2,4) = inMatrix.d2;

	result(3,1) = inMatrix.a3;
	result(3,2) = inMatrix.b3;
	result(3,3) = inMatrix.c3;
	result(3,4) = inMatrix.d3;

	result(4,1) = inMatrix.a4;
	result(4,2) = inMatrix.b4;
	result(4,3) = inMatrix.c4;
	result(4,4) = inMatrix.d4;
}

}