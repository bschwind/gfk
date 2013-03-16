#include <GFK/Graphics/Color.hpp>

namespace gfk
{

Color::Color()
{
	R = G = B = 0.0f;
	A = 1.0f;
}

Color::Color(const float r, const float g, const float b)
{
	R = r; G = g; B = b;
	A = 1.0f;
}

Color::Color(const float r, const float g, const float b, const float a)
{
	R = r; G = g; B = b; A = a;
}

Color::Color(unsigned int color)
{
	unsigned int mask = 0x000000ff;
	A = (float)((color >> 24 & mask))/(255.0f);
	B = (float)((color >> 16 & mask))/(255.0f);
	G = (float)((color >> 8 & mask))/(255.0f);
	R = (float)((color & mask))/(255.0f);
}

Color::~Color()
{

}

const Color Color::TransparentBlack = Color(0x00000000);
const Color Color::Transparent = Color(0x00000000);
const Color Color::AliceBlue = Color(0xfffff8f0);
const Color Color::AntiqueWhite = Color(0xffd7ebfa);
const Color Color::Aqua = Color(0xffffff00);
const Color Color::Aquamarine = Color(0xffd4ff7f);
const Color Color::Azure = Color(0xfffffff0);
const Color Color::Beige = Color(0xffdcf5f5);
const Color Color::Bisque = Color(0xffc4e4ff);
const Color Color::Black = Color(0xff000000);
const Color Color::BlanchedAlmond = Color(0xffcdebff);
const Color Color::Blue = Color(0xffff0000);
const Color Color::BlueViolet = Color(0xffe22b8a);
const Color Color::Brown = Color(0xff2a2aa5);
const Color Color::BurlyWood = Color(0xff87b8de);
const Color Color::CadetBlue = Color(0xffa09e5f);
const Color Color::Chartreuse = Color(0xff00ff7f);
const Color Color::Chocolate = Color(0xff1e69d2);
const Color Color::Coral = Color(0xff507fff);
const Color Color::CornflowerBlue = Color(0xffed9564);
const Color Color::Cornsilk = Color(0xffdcf8ff);
const Color Color::Crimson = Color(0xff3c14dc);
const Color Color::Cyan = Color(0xffffff00);
const Color Color::DarkBlue = Color(0xff8b0000);
const Color Color::DarkCyan = Color(0xff8b8b00);
const Color Color::DarkGoldenrod = Color(0xff0b86b8);
const Color Color::DarkGray = Color(0xffa9a9a9);
const Color Color::DarkGreen = Color(0xff006400);
const Color Color::DarkKhaki = Color(0xff6bb7bd);
const Color Color::DarkMagenta = Color(0xff8b008b);
const Color Color::DarkOliveGreen = Color(0xff2f6b55);
const Color Color::DarkOrange = Color(0xff008cff);
const Color Color::DarkOrchid = Color(0xffcc3299);
const Color Color::DarkRed = Color(0xff00008b);
const Color Color::DarkSalmon = Color(0xff7a96e9);
const Color Color::DarkSeaGreen = Color(0xff8bbc8f);
const Color Color::DarkSlateBlue = Color(0xff8b3d48);
const Color Color::DarkSlateGray = Color(0xff4f4f2f);
const Color Color::DarkTurquoise = Color(0xffd1ce00);
const Color Color::DarkViolet = Color(0xffd30094);
const Color Color::DeepPink = Color(0xff9314ff);
const Color Color::DeepSkyBlue = Color(0xffffbf00);
const Color Color::DimGray = Color(0xff696969);
const Color Color::DodgerBlue = Color(0xffff901e);
const Color Color::Firebrick = Color(0xff2222b2);
const Color Color::FloralWhite = Color(0xfff0faff);
const Color Color::ForestGreen = Color(0xff228b22);
const Color Color::Fuchsia = Color(0xffff00ff);
const Color Color::Gainsboro = Color(0xffdcdcdc);
const Color Color::GhostWhite = Color(0xfffff8f8);
const Color Color::Gold = Color(0xff00d7ff);
const Color Color::Goldenrod = Color(0xff20a5da);
const Color Color::Gray = Color(0xff808080);
const Color Color::Green = Color(0xff008000);
const Color Color::GreenYellow = Color(0xff2fffad);
const Color Color::Honeydew = Color(0xfff0fff0);
const Color Color::HotPink = Color(0xffb469ff);
const Color Color::IndianRed = Color(0xff5c5ccd);
const Color Color::Indigo = Color(0xff82004b);
const Color Color::Ivory = Color(0xfff0ffff);
const Color Color::Khaki = Color(0xff8ce6f0);
const Color Color::Lavender = Color(0xfffae6e6);
const Color Color::LavenderBlush = Color(0xfff5f0ff);
const Color Color::LawnGreen = Color(0xff00fc7c);
const Color Color::LemonChiffon = Color(0xffcdfaff);
const Color Color::LightBlue = Color(0xffe6d8ad);
const Color Color::LightCoral = Color(0xff8080f0);
const Color Color::LightCyan = Color(0xffffffe0);
const Color Color::LightGoldenrodYellow = Color(0xffd2fafa);
const Color Color::LightGray = Color(0xffd3d3d3);
const Color Color::LightGreen = Color(0xff90ee90);
const Color Color::LightPink = Color(0xffc1b6ff);
const Color Color::LightSalmon = Color(0xff7aa0ff);
const Color Color::LightSeaGreen = Color(0xffaab220);
const Color Color::LightSkyBlue = Color(0xffface87);
const Color Color::LightSlateGray = Color(0xff998877);
const Color Color::LightSteelBlue = Color(0xffdec4b0);
const Color Color::LightYellow = Color(0xffe0ffff);
const Color Color::Lime = Color(0xff00ff00);
const Color Color::LimeGreen = Color(0xff32cd32);
const Color Color::Linen = Color(0xffe6f0fa);
const Color Color::Magenta = Color(0xffff00ff);
const Color Color::Maroon = Color(0xff000080);
const Color Color::MediumAquamarine = Color(0xffaacd66);
const Color Color::MediumBlue = Color(0xffcd0000);
const Color Color::MediumOrchid = Color(0xffd355ba);
const Color Color::MediumPurple = Color(0xffdb7093); 
const Color MediumSeaGreen = Color(0xff71b33c);
const Color Color::MediumSlateBlue = Color(0xffee687b);
const Color Color::MediumSpringGreen = Color(0xff9afa00);
const Color Color::MediumTurquoise = Color(0xffccd148);
const Color Color::MediumVioletRed = Color(0xff8515c7);
const Color Color::MidnightBlue = Color(0xff701919);
const Color Color::MintCream = Color(0xfffafff5);
const Color Color::MistyRose = Color(0xffe1e4ff);
const Color Color::Moccasin = Color(0xffb5e4ff);
const Color Color::NavajoWhite = Color(0xffaddeff);
const Color Color::Navy = Color(0xff800000);
const Color Color::OldLace = Color(0xffe6f5fd);
const Color Color::Olive = Color(0xff008080);
const Color Color::OliveDrab = Color(0xff238e6b);
const Color Color::Orange = Color(0xff00a5ff);
const Color Color::OrangeRed = Color(0xff0045ff);
const Color Color::Orchid = Color(0xffd670da);
const Color Color::PaleGoldenrod = Color(0xffaae8ee);
const Color Color::PaleGreen = Color(0xff98fb98);
const Color Color::PaleTurquoise = Color(0xffeeeeaf); 
const Color Color::PaleVioletRed = Color(0xff9370db);
const Color Color::PapayaWhip = Color(0xffd5efff);
const Color Color::PeachPuff = Color(0xffb9daff);
const Color Color::Peru = Color(0xff3f85cd);
const Color Color::Pink = Color(0xffcbc0ff);
const Color Color::Plum = Color(0xffdda0dd);
const Color Color::PowderBlue = Color(0xffe6e0b0);
const Color Color::Purple = Color(0xff800080);
const Color Color::Red = Color(0xff0000ff);
const Color Color::RosyBrown = Color(0xff8f8fbc);
const Color Color::RoyalBlue = Color(0xffe16941);
const Color Color::SaddleBrown = Color(0xff13458b);
const Color Color::Salmon = Color(0xff7280fa);
const Color Color::SandyBrown = Color(0xff60a4f4);
const Color Color::SeaGreen = Color(0xff578b2e);
const Color Color::SeaShell = Color(0xffeef5ff);
const Color Color::Sienna = Color(0xff2d52a0);
const Color Color::Silver = Color(0xffc0c0c0);
const Color Color::SkyBlue = Color(0xffebce87);
const Color Color::SlateBlue = Color(0xffcd5a6a);
const Color Color::SlateGray = Color(0xff908070);
const Color Color::Snow = Color(0xfffafaff);
const Color Color::SpringGreen = Color(0xff7fff00);
const Color Color::SteelBlue = Color(0xffb48246);
const Color Color::Tan = Color(0xff8cb4d2);
const Color Color::Teal = Color(0xff808000);
const Color Color::Thistle = Color(0xffd8bfd8);
const Color Color::Tomato = Color(0xff4763ff);
const Color Color::Turquoise = Color(0xffd0e040);
const Color Color::Violet = Color(0xffee82ee);
const Color Color::Wheat = Color(0xffb3def5);
const Color Color::White = Color(0xffffffff);
const Color Color::WhiteSmoke = Color(0xfff5f5f5);
const Color Color::Yellow = Color(0xff00ffff);
const Color Color::YellowGreen = Color(0xff32cd9a);

}