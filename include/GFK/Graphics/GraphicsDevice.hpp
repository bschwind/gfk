#include <SFML/Window.hpp>
#include <GFK/Graphics/Color.hpp>

namespace gfk
{
class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	void SetClearColor(const gfk::Color color);
	void SetDepthClearValue(const float depth);
	void Clear();
	void ClearDepth();
	void ClearColor();
protected:

private:

};
}
