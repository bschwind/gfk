namespace gfk
{
class Color
{
public:
	Color();
	Color(const float r, const float g, const float b);
	Color(const float r, const float g, const float b, const float a);
	~Color();

	float R, G, B, A;
};
}
