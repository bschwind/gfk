#include <GFK/Graphics/PackedColor.hpp>

namespace gfk
{

const float PackedColor::divisor(1.0f/255.0f);

PackedColor::PackedColor()
{
	packedValue = 0xff000000;
}

PackedColor::PackedColor(const float r, const float g, const float b)
{
	packedValue = 0;
	packedValue |= ((unsigned char)(r * 255));
	packedValue |= ((unsigned char)(g * 255) << 8);
	packedValue |= ((unsigned char)(b * 255) << 16);
	packedValue |= 0xff000000;
}

PackedColor::PackedColor(const float r, const float g, const float b, const float a)
{
	packedValue = 0;
	packedValue |= ((unsigned char)(r * 255));
	packedValue |= ((unsigned char)(g * 255) << 8);
	packedValue |= ((unsigned char)(b * 255) << 16);
	packedValue |= ((unsigned char)(b * 255) << 24);
}

PackedColor::PackedColor(unsigned int color)
{
	packedValue = color;
}

PackedColor::~PackedColor()
{

}

const PackedColor PackedColor::TransparentBlack(0x00000000);
const PackedColor PackedColor::Transparent(0x00000000);
const PackedColor PackedColor::AliceBlue(0xfffff8f0);
const PackedColor PackedColor::AntiqueWhite(0xffd7ebfa);
const PackedColor PackedColor::Aqua(0xffffff00);
const PackedColor PackedColor::Aquamarine(0xffd4ff7f);
const PackedColor PackedColor::Azure(0xfffffff0);
const PackedColor PackedColor::Beige(0xffdcf5f5);
const PackedColor PackedColor::Bisque(0xffc4e4ff);
const PackedColor PackedColor::Black(0xff000000);
const PackedColor PackedColor::BlanchedAlmond(0xffcdebff);
const PackedColor PackedColor::Blue(0xffff0000);
const PackedColor PackedColor::BlueViolet(0xffe22b8a);
const PackedColor PackedColor::Brown(0xff2a2aa5);
const PackedColor PackedColor::BurlyWood(0xff87b8de);
const PackedColor PackedColor::CadetBlue(0xffa09e5f);
const PackedColor PackedColor::Chartreuse(0xff00ff7f);
const PackedColor PackedColor::Chocolate(0xff1e69d2);
const PackedColor PackedColor::Coral(0xff507fff);
const PackedColor PackedColor::CornflowerBlue(0xffed9564);
const PackedColor PackedColor::Cornsilk(0xffdcf8ff);
const PackedColor PackedColor::Crimson(0xff3c14dc);
const PackedColor PackedColor::Cyan(0xffffff00);
const PackedColor PackedColor::DarkBlue(0xff8b0000);
const PackedColor PackedColor::DarkCyan(0xff8b8b00);
const PackedColor PackedColor::DarkGoldenrod(0xff0b86b8);
const PackedColor PackedColor::DarkGray(0xffa9a9a9);
const PackedColor PackedColor::DarkGreen(0xff006400);
const PackedColor PackedColor::DarkKhaki(0xff6bb7bd);
const PackedColor PackedColor::DarkMagenta(0xff8b008b);
const PackedColor PackedColor::DarkOliveGreen(0xff2f6b55);
const PackedColor PackedColor::DarkOrange(0xff008cff);
const PackedColor PackedColor::DarkOrchid(0xffcc3299);
const PackedColor PackedColor::DarkRed(0xff00008b);
const PackedColor PackedColor::DarkSalmon(0xff7a96e9);
const PackedColor PackedColor::DarkSeaGreen(0xff8bbc8f);
const PackedColor PackedColor::DarkSlateBlue(0xff8b3d48);
const PackedColor PackedColor::DarkSlateGray(0xff4f4f2f);
const PackedColor PackedColor::DarkTurquoise(0xffd1ce00);
const PackedColor PackedColor::DarkViolet(0xffd30094);
const PackedColor PackedColor::DeepPink(0xff9314ff);
const PackedColor PackedColor::DeepSkyBlue(0xffffbf00);
const PackedColor PackedColor::DimGray(0xff696969);
const PackedColor PackedColor::DodgerBlue(0xffff901e);
const PackedColor PackedColor::Firebrick(0xff2222b2);
const PackedColor PackedColor::FloralWhite(0xfff0faff);
const PackedColor PackedColor::ForestGreen(0xff228b22);
const PackedColor PackedColor::Fuchsia(0xffff00ff);
const PackedColor PackedColor::Gainsboro(0xffdcdcdc);
const PackedColor PackedColor::GhostWhite(0xfffff8f8);
const PackedColor PackedColor::Gold(0xff00d7ff);
const PackedColor PackedColor::Goldenrod(0xff20a5da);
const PackedColor PackedColor::Gray(0xff808080);
const PackedColor PackedColor::Green(0xff008000);
const PackedColor PackedColor::GreenYellow(0xff2fffad);
const PackedColor PackedColor::Honeydew(0xfff0fff0);
const PackedColor PackedColor::HotPink(0xffb469ff);
const PackedColor PackedColor::IndianRed(0xff5c5ccd);
const PackedColor PackedColor::Indigo(0xff82004b);
const PackedColor PackedColor::Ivory(0xfff0ffff);
const PackedColor PackedColor::Khaki(0xff8ce6f0);
const PackedColor PackedColor::Lavender(0xfffae6e6);
const PackedColor PackedColor::LavenderBlush(0xfff5f0ff);
const PackedColor PackedColor::LawnGreen(0xff00fc7c);
const PackedColor PackedColor::LemonChiffon(0xffcdfaff);
const PackedColor PackedColor::LightBlue(0xffe6d8ad);
const PackedColor PackedColor::LightCoral(0xff8080f0);
const PackedColor PackedColor::LightCyan(0xffffffe0);
const PackedColor PackedColor::LightGoldenrodYellow(0xffd2fafa);
const PackedColor PackedColor::LightGray(0xffd3d3d3);
const PackedColor PackedColor::LightGreen(0xff90ee90);
const PackedColor PackedColor::LightPink(0xffc1b6ff);
const PackedColor PackedColor::LightSalmon(0xff7aa0ff);
const PackedColor PackedColor::LightSeaGreen(0xffaab220);
const PackedColor PackedColor::LightSkyBlue(0xffface87);
const PackedColor PackedColor::LightSlateGray(0xff998877);
const PackedColor PackedColor::LightSteelBlue(0xffdec4b0);
const PackedColor PackedColor::LightYellow(0xffe0ffff);
const PackedColor PackedColor::Lime(0xff00ff00);
const PackedColor PackedColor::LimeGreen(0xff32cd32);
const PackedColor PackedColor::Linen(0xffe6f0fa);
const PackedColor PackedColor::Magenta(0xffff00ff);
const PackedColor PackedColor::Maroon(0xff000080);
const PackedColor PackedColor::MediumAquamarine(0xffaacd66);
const PackedColor PackedColor::MediumBlue(0xffcd0000);
const PackedColor PackedColor::MediumOrchid(0xffd355ba);
const PackedColor PackedColor::MediumPurple(0xffdb7093); 
const PackedColor PackedColor::MediumSeaGreen(0xff71b33c);
const PackedColor PackedColor::MediumSlateBlue(0xffee687b);
const PackedColor PackedColor::MediumSpringGreen(0xff9afa00);
const PackedColor PackedColor::MediumTurquoise(0xffccd148);
const PackedColor PackedColor::MediumVioletRed(0xff8515c7);
const PackedColor PackedColor::MidnightBlue(0xff701919);
const PackedColor PackedColor::MintCream(0xfffafff5);
const PackedColor PackedColor::MistyRose(0xffe1e4ff);
const PackedColor PackedColor::Moccasin(0xffb5e4ff);
const PackedColor PackedColor::NavajoWhite(0xffaddeff);
const PackedColor PackedColor::Navy(0xff800000);
const PackedColor PackedColor::OldLace(0xffe6f5fd);
const PackedColor PackedColor::Olive(0xff008080);
const PackedColor PackedColor::OliveDrab(0xff238e6b);
const PackedColor PackedColor::Orange(0xff00a5ff);
const PackedColor PackedColor::OrangeRed(0xff0045ff);
const PackedColor PackedColor::Orchid(0xffd670da);
const PackedColor PackedColor::PaleGoldenrod(0xffaae8ee);
const PackedColor PackedColor::PaleGreen(0xff98fb98);
const PackedColor PackedColor::PaleTurquoise(0xffeeeeaf); 
const PackedColor PackedColor::PaleVioletRed(0xff9370db);
const PackedColor PackedColor::PapayaWhip(0xffd5efff);
const PackedColor PackedColor::PeachPuff(0xffb9daff);
const PackedColor PackedColor::Peru(0xff3f85cd);
const PackedColor PackedColor::Pink(0xffcbc0ff);
const PackedColor PackedColor::Plum(0xffdda0dd);
const PackedColor PackedColor::PowderBlue(0xffe6e0b0);
const PackedColor PackedColor::Purple(0xff800080);
const PackedColor PackedColor::Red(0xff0000ff);
const PackedColor PackedColor::RosyBrown(0xff8f8fbc);
const PackedColor PackedColor::RoyalBlue(0xffe16941);
const PackedColor PackedColor::SaddleBrown(0xff13458b);
const PackedColor PackedColor::Salmon(0xff7280fa);
const PackedColor PackedColor::SandyBrown(0xff60a4f4);
const PackedColor PackedColor::SeaGreen(0xff578b2e);
const PackedColor PackedColor::SeaShell(0xffeef5ff);
const PackedColor PackedColor::Sienna(0xff2d52a0);
const PackedColor PackedColor::Silver(0xffc0c0c0);
const PackedColor PackedColor::SkyBlue(0xffebce87);
const PackedColor PackedColor::SlateBlue(0xffcd5a6a);
const PackedColor PackedColor::SlateGray(0xff908070);
const PackedColor PackedColor::Snow(0xfffafaff);
const PackedColor PackedColor::SpringGreen(0xff7fff00);
const PackedColor PackedColor::SteelBlue(0xffb48246);
const PackedColor PackedColor::Tan(0xff8cb4d2);
const PackedColor PackedColor::Teal(0xff808000);
const PackedColor PackedColor::Thistle(0xffd8bfd8);
const PackedColor PackedColor::Tomato(0xff4763ff);
const PackedColor PackedColor::Turquoise(0xffd0e040);
const PackedColor PackedColor::Violet(0xffee82ee);
const PackedColor PackedColor::Wheat(0xffb3def5);
const PackedColor PackedColor::White(0xffffffff);
const PackedColor PackedColor::WhiteSmoke(0xfff5f5f5);
const PackedColor PackedColor::Yellow(0xff00ffff);
const PackedColor PackedColor::YellowGreen(0xff32cd9a);

}