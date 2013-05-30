#pragma once

namespace gfk
{
class PackedColor
{
private:
	unsigned int packedValue;
	static const float divisor;

public:
	PackedColor();
	PackedColor(float r, float g, float b);
	PackedColor(float r, float g, float b, float a);
	PackedColor(const unsigned int PackedColor);
	~PackedColor();

	inline float GetR() const
	{
		return (packedValue & 0x000000ff) * divisor;
	}

	inline float GetG() const
	{
		return ((packedValue & 0x0000ff00) >> 8) * divisor;
	}

	inline float GetB() const
	{
		return ((packedValue & 0x00ff0000) >> 16) * divisor;
	}

	inline float GetA() const
	{
		return ((packedValue & 0xff000000) >> 24) * divisor;
	}

	/// TransparentBlack (R:0,G:0,B:0,A:0)
	static const PackedColor TransparentBlack;

	/// Transparent (R:0,G:0,B:0,A:0)
	static const PackedColor Transparent;

	/// AliceBlue (R:240,G:248,B:255,A:255)
	static const PackedColor AliceBlue;

	/// AntiqueWhite (R:250,G:235,B:215,A:255)
	static const PackedColor AntiqueWhite;

	/// Aqua (R:0,G:255,B:255,A:255)
	static const PackedColor Aqua;

	/// Aquamarine (R:127,G:255,B:212,A:255)
	static const PackedColor Aquamarine;

	/// Azure (R:240,G:255,B:255,A:255)
	static const PackedColor Azure;

	/// Beige (R:245,G:245,B:220,A:255)
	static const PackedColor Beige;

	/// Bisque (R:255,G:228,B:196,A:255)
	static const PackedColor Bisque;

	/// Black (R:0,G:0,B:0,A:255)
	static const PackedColor Black;

	/// BlanchedAlmond (R:255,G:235,B:205,A:255)
	static const PackedColor BlanchedAlmond;

	/// Blue (R:0,G:0,B:255,A:255)
	static const PackedColor Blue;

	/// BlueViolet (R:138,G:43,B:226,A:255)
	static const PackedColor BlueViolet;

	/// Brown (R:165,G:42,B:42,A:255)
	static const PackedColor Brown;

	/// BurlyWood (R:222,G:184,B:135,A:255)
	static const PackedColor BurlyWood;

	/// CadetBlue (R:95,G:158,B:160,A:255)
	static const PackedColor CadetBlue;

	/// Chartreuse (R:127,G:255,B:0,A:255)
	static const PackedColor Chartreuse;

	/// Chocolate (R:210,G:105,B:30,A:255)
	static const PackedColor Chocolate;

	/// Coral (R:255,G:127,B:80,A:255)
	static const PackedColor Coral;

	/// CornflowerBlue (R:100,G:149,B:237,A:255)
	static const PackedColor CornflowerBlue;

	/// Cornsilk (R:255,G:248,B:220,A:255)
	static const PackedColor Cornsilk;

	/// Crimson (R:220,G:20,B:60,A:255)
	static const PackedColor Crimson;

	/// Cyan (R:0,G:255,B:255,A:255)
	static const PackedColor Cyan;

	/// DarkBlue (R:0,G:0,B:139,A:255)
	static const PackedColor DarkBlue;

	/// DarkCyan (R:0,G:139,B:139,A:255)
	static const PackedColor DarkCyan;

	/// DarkGoldenrod (R:184,G:134,B:11,A:255)
	static const PackedColor DarkGoldenrod;

	/// DarkGray (R:169,G:169,B:169,A:255)
	static const PackedColor DarkGray;

	/// DarkGreen (R:0,G:100,B:0,A:255)
	static const PackedColor DarkGreen;

	/// DarkKhaki (R:189,G:183,B:107,A:255)
	static const PackedColor DarkKhaki;

	/// DarkMagenta (R:139,G:0,B:139,A:255)
	static const PackedColor DarkMagenta;

	/// DarkOliveGreen (R:85,G:107,B:47,A:255)
	static const PackedColor DarkOliveGreen;

	/// DarkOrange (R:255,G:140,B:0,A:255)
	static const PackedColor DarkOrange;

	/// DarkOrchid (R:153,G:50,B:204,A:255)
	static const PackedColor DarkOrchid;

	/// DarkRed (R:139,G:0,B:0,A:255)
	static const PackedColor DarkRed;

	/// DarkSalmon (R:233,G:150,B:122,A:255)
	static const PackedColor DarkSalmon;

	/// DarkSeaGreen (R:143,G:188,B:139,A:255)
	static const PackedColor DarkSeaGreen;

	/// DarkSlateBlue (R:72,G:61,B:139,A:255)
	static const PackedColor DarkSlateBlue;

	/// DarkSlateGray (R:47,G:79,B:79,A:255)
	static const PackedColor DarkSlateGray;

	/// DarkTurquoise (R:0,G:206,B:209,A:255)
	static const PackedColor DarkTurquoise;

	/// DarkViolet (R:148,G:0,B:211,A:255)
	static const PackedColor DarkViolet;

	/// DeepPink (R:255,G:20,B:147,A:255)
	static const PackedColor DeepPink;

	/// DeepSkyBlue (R:0,G:191,B:255,A:255)
	static const PackedColor DeepSkyBlue;

	/// DimGray (R:105,G:105,B:105,A:255)
	static const PackedColor DimGray;

	/// DodgerBlue (R:30,G:144,B:255,A:255)
	static const PackedColor DodgerBlue;

	/// Firebrick (R:178,G:34,B:34,A:255)
	static const PackedColor Firebrick;

	/// FloralWhite (R:255,G:250,B:240,A:255)
	static const PackedColor FloralWhite;

	/// ForestGreen (R:34,G:139,B:34,A:255)
	static const PackedColor ForestGreen;

	/// Fuchsia (R:255,G:0,B:255,A:255)
	static const PackedColor Fuchsia;

	/// Gainsboro (R:220,G:220,B:220,A:255)
	static const PackedColor Gainsboro;

	/// GhostWhite (R:248,G:248,B:255,A:255)
	static const PackedColor GhostWhite;

	/// Gold (R:255,G:215,B:0,A:255)
	static const PackedColor Gold;

	/// Goldenrod (R:218,G:165,B:32,A:255)
	static const PackedColor Goldenrod;

	/// Gray (R:128,G:128,B:128,A:255)
	static const PackedColor Gray;

	/// Green (R:0,G:128,B:0,A:255)
	static const PackedColor Green;

	/// GreenYellow (R:173,G:255,B:47,A:255)
	static const PackedColor GreenYellow;

	/// Honeydew (R:240,G:255,B:240,A:255)
	static const PackedColor Honeydew;

	/// HotPink (R:255,G:105,B:180,A:255)
	static const PackedColor HotPink;

	/// IndianRed (R:205,G:92,B:92,A:255)
	static const PackedColor IndianRed;

	/// Indigo (R:75,G:0,B:130,A:255)
	static const PackedColor Indigo;

	/// Ivory (R:255,G:255,B:240,A:255)
	static const PackedColor Ivory;

	/// Khaki (R:240,G:230,B:140,A:255)
	static const PackedColor Khaki;

	/// Lavender (R:230,G:230,B:250,A:255)
	static const PackedColor Lavender;

	/// LavenderBlush (R:255,G:240,B:245,A:255)
	static const PackedColor LavenderBlush;

	/// LawnGreen (R:124,G:252,B:0,A:255)
	static const PackedColor LawnGreen;

	/// LemonChiffon (R:255,G:250,B:205,A:255)
	static const PackedColor LemonChiffon;

	/// LightBlue (R:173,G:216,B:230,A:255)
	static const PackedColor LightBlue;

	/// LightCoral (R:240,G:128,B:128,A:255)
	static const PackedColor LightCoral;

	/// LightCyan (R:224,G:255,B:255,A:255)
	static const PackedColor LightCyan;

	/// LightGoldenrodYellow (R:250,G:250,B:210,A:255)
	static const PackedColor LightGoldenrodYellow;

	/// LightGray (R:211,G:211,B:211,A:255)
	static const PackedColor LightGray;

	/// LightGreen (R:144,G:238,B:144,A:255)
	static const PackedColor LightGreen;

	/// LightPink (R:255,G:182,B:193,A:255)
	static const PackedColor LightPink;

	/// LightSalmon (R:255,G:160,B:122,A:255)
	static const PackedColor LightSalmon;

	/// LightSeaGreen (R:32,G:178,B:170,A:255)
	static const PackedColor LightSeaGreen;

	/// LightSkyBlue (R:135,G:206,B:250,A:255)
	static const PackedColor LightSkyBlue;

	/// LightSlateGray (R:119,G:136,B:153,A:255)
	static const PackedColor LightSlateGray;

	/// LightSteelBlue (R:176,G:196,B:222,A:255)
	static const PackedColor LightSteelBlue;

	/// LightYellow (R:255,G:255,B:224,A:255)
	static const PackedColor LightYellow;

	/// Lime (R:0,G:255,B:0,A:255)
	static const PackedColor Lime;

	/// LimeGreen (R:50,G:205,B:50,A:255)
	static const PackedColor LimeGreen;

	/// Linen (R:250,G:240,B:230,A:255)
	static const PackedColor Linen;

	/// Magenta (R:255,G:0,B:255,A:255)
	static const PackedColor Magenta;

	/// Maroon (R:128,G:0,B:0,A:255)
	static const PackedColor Maroon;

	/// MediumAquamarine (R:102,G:205,B:170,A:255)
	static const PackedColor MediumAquamarine;

	/// MediumBlue (R:0,G:0,B:205,A:255)
	static const PackedColor MediumBlue;

	/// MediumOrchid (R:186,G:85,B:211,A:255)
	static const PackedColor MediumOrchid;

	/// MediumPurple (R:147,G:112,B:219,A:255)
	static const PackedColor MediumPurple;

	/// MediumSeaGreen (R:60,G:179,B:113,A:255)
	static const PackedColor MediumSeaGreen;

	/// MediumSlateBlue (R:123,G:104,B:238,A:255)
	static const PackedColor MediumSlateBlue;

	/// MediumSpringGreen (R:0,G:250,B:154,A:255)
	static const PackedColor MediumSpringGreen;

	/// MediumTurquoise (R:72,G:209,B:204,A:255)
	static const PackedColor MediumTurquoise;

	/// MediumVioletRed (R:199,G:21,B:133,A:255)
	static const PackedColor MediumVioletRed;

	/// MidnightBlue (R:25,G:25,B:112,A:255)
	static const PackedColor MidnightBlue;

	/// MintCream (R:245,G:255,B:250,A:255)
	static const PackedColor MintCream;

	/// MistyRose (R:255,G:228,B:225,A:255)
	static const PackedColor MistyRose;

	/// Moccasin (R:255,G:228,B:181,A:255)
	static const PackedColor Moccasin;

	/// NavajoWhite (R:255,G:222,B:173,A:255)
	static const PackedColor NavajoWhite;

	/// Navy (R:0,G:0,B:128,A:255)
	static const PackedColor Navy;

	/// OldLace (R:253,G:245,B:230,A:255)
	static const PackedColor OldLace;

	/// Olive (R:128,G:128,B:0,A:255)
	static const PackedColor Olive;

	/// OliveDrab (R:107,G:142,B:35,A:255)
	static const PackedColor OliveDrab;

	/// Orange (R:255,G:165,B:0,A:255)
	static const PackedColor Orange;

	/// OrangeRed (R:255,G:69,B:0,A:255)
	static const PackedColor OrangeRed;

	/// Orchid (R:218,G:112,B:214,A:255)
	static const PackedColor Orchid;

	/// PaleGoldenrod (R:238,G:232,B:170,A:255)
	static const PackedColor PaleGoldenrod;

	/// PaleGreen (R:152,G:251,B:152,A:255)
	static const PackedColor PaleGreen;

	/// PaleTurquoise (R:175,G:238,B:238,A:255)
	static const PackedColor PaleTurquoise;

	/// PaleVioletRed (R:219,G:112,B:147,A:255)
	static const PackedColor PaleVioletRed;

	/// PapayaWhip (R:255,G:239,B:213,A:255)
	static const PackedColor PapayaWhip;

	/// PeachPuff (R:255,G:218,B:185,A:255)
	static const PackedColor PeachPuff;

	/// Peru (R:205,G:133,B:63,A:255)
	static const PackedColor Peru;

	/// Pink (R:255,G:192,B:203,A:255)
	static const PackedColor Pink;

	/// Plum (R:221,G:160,B:221,A:255)
	static const PackedColor Plum;

	/// PowderBlue (R:176,G:224,B:230,A:255)
	static const PackedColor PowderBlue;

	///  Purple (R:128,G:0,B:128,A:255)
	static const PackedColor Purple;

	/// Red (R:255,G:0,B:0,A:255)
	static const PackedColor Red;

	/// RosyBrown (R:188,G:143,B:143,A:255)
	static const PackedColor RosyBrown;

	/// RoyalBlue (R:65,G:105,B:225,A:255)
	static const PackedColor RoyalBlue;

	/// SaddleBrown (R:139,G:69,B:19,A:255)
	static const PackedColor SaddleBrown;

	/// Salmon (R:250,G:128,B:114,A:255)
	static const PackedColor Salmon;

	/// SandyBrown (R:244,G:164,B:96,A:255)
	static const PackedColor SandyBrown;

	/// SeaGreen (R:46,G:139,B:87,A:255)
	static const PackedColor SeaGreen;

	/// SeaShell (R:255,G:245,B:238,A:255)
	static const PackedColor SeaShell;

	/// Sienna (R:160,G:82,B:45,A:255)
	static const PackedColor Sienna;

	/// Silver (R:192,G:192,B:192,A:255)
	static const PackedColor Silver;

	/// SkyBlue (R:135,G:206,B:235,A:255)
	static const PackedColor SkyBlue;

	/// SlateBlue (R:106,G:90,B:205,A:255)
	static const PackedColor SlateBlue;

	/// SlateGray (R:112,G:128,B:144,A:255)
	static const PackedColor SlateGray;

	/// Snow (R:255,G:250,B:250,A:255)
	static const PackedColor Snow;

	/// SpringGreen (R:0,G:255,B:127,A:255)
	static const PackedColor SpringGreen;

	/// SteelBlue (R:70,G:130,B:180,A:255)
	static const PackedColor SteelBlue;

	/// Tan (R:210,G:180,B:140,A:255)
	static const PackedColor Tan;

	/// Teal (R:0,G:128,B:128,A:255)
	static const PackedColor Teal;

	/// Thistle (R:216,G:191,B:216,A:255)
	static const PackedColor Thistle;

	/// Tomato (R:255,G:99,B:71,A:255)
	static const PackedColor Tomato;

	/// Turquoise (R:64,G:224,B:208,A:255)
	static const PackedColor Turquoise;

	/// Violet (R:238,G:130,B:238,A:255)
	static const PackedColor Violet;

	/// Wheat (R:245,G:222,B:179,A:255)
	static const PackedColor Wheat;

	/// White (R:255,G:255,B:255,A:255)
	static const PackedColor White;

	/// WhiteSmoke (R:245,G:245,B:245,A:255)
	static const PackedColor WhiteSmoke;

	/// Yellow (R:255,G:255,B:0,A:255)
	static const PackedColor Yellow;

	/// YellowGreen (R:154,G:205,B:50,A:255)
	static const PackedColor YellowGreen;
};

}
