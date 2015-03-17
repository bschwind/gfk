#include "objects/GameInput.hpp"

namespace jetGame
{

GameInput::GameInput() :
sequenceNumber(0),
mouseDiffX(0.0f),
mouseDiffY(0.0f),
keyW(false),
keyS(false),
keyLeftShift(false)
{

}

GameInput::~GameInput()
{

}

}
