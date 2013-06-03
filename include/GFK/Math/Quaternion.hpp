#pragma once

namespace gfk
{

class Quaternion
{
public:
	float X, Y, Z, W;
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	~Quaternion();

	static const Quaternion Identity;
protected:
private:
};

}