#pragma once

#include <GFK/ConsoleGame.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Mesh.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>

using namespace gfk;

namespace jetGame
{

class JetServer : public ConsoleGame
{
public:
	JetServer();
	~JetServer();
	virtual void Initialize();
	virtual void UnloadContent();
protected:
	virtual void LoadContent();
	virtual void Update(const gfk::GameTime &gameTime);
private:
	UDPSocket socket;
	NetworkBuffer netBuffer;
};

}