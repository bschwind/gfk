#pragma once

namespace jetGame
{

class GameInput
{
public:
	GameInput();
	~GameInput();

	unsigned int sequenceNumber;
	float mouseDiffX;
	float mouseDiffY;
	bool keyW;
	bool keyS;
	bool keyA;
	bool keyD;
	bool keyLeftShift;
protected:
private:
};

}
