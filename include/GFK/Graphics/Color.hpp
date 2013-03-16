namespace gfk
{
class Color
{
public:
	Color();
	Color(const float r, const float g, const float b);
	Color(const float r, const float g, const float b, const float a);
	Color(const unsigned int color);
	~Color();

	float R, G, B, A;

	/// TransparentBlack color (R:0,G:0,B:0,A:0).
	static const Color TransparentBlack;

	/// Transparent color (R:0,G:0,B:0,A:0).
	static const Color Transparent;

	/// AliceBlue color (R:240,G:248,B:255,A:255).
	static const Color AliceBlue;

	/// AntiqueWhite color (R:250,G:235,B:215,A:255).
	static const Color AntiqueWhite;

	/// Aqua color (R:0,G:255,B:255,A:255).
	static const Color Aqua;

	/// Aquamarine color (R:127,G:255,B:212,A:255).
	static const Color Aquamarine;

	/// Azure color (R:240,G:255,B:255,A:255).
	static const Color Azure;

	/// Beige color (R:245,G:245,B:220,A:255).
	static const Color Beige;

	/// Bisque color (R:255,G:228,B:196,A:255).
	static const Color Bisque;

	/// Black color (R:0,G:0,B:0,A:255).
	static const Color Black;

	/// BlanchedAlmond color (R:255,G:235,B:205,A:255).
	static const Color BlanchedAlmond;

	/// Blue color (R:0,G:0,B:255,A:255).
	static const Color Blue;

	/// BlueViolet color (R:138,G:43,B:226,A:255).
	static const Color BlueViolet;

	/// Brown color (R:165,G:42,B:42,A:255).
	static const Color Brown;

	/// BurlyWood color (R:222,G:184,B:135,A:255).
	static const Color BurlyWood;

	/// CadetBlue color (R:95,G:158,B:160,A:255).
	static const Color CadetBlue;

	/// Chartreuse color (R:127,G:255,B:0,A:255).
	static const Color Chartreuse;

	/// Chocolate color (R:210,G:105,B:30,A:255).
	static const Color Chocolate;

	/// Coral color (R:255,G:127,B:80,A:255).
	static const Color Coral;

	/// CornflowerBlue color (R:100,G:149,B:237,A:255).
	static const Color CornflowerBlue;

	/// Cornsilk color (R:255,G:248,B:220,A:255).
	static const Color Cornsilk;

	/// Crimson color (R:220,G:20,B:60,A:255).
	static const Color Crimson;

	/// Cyan color (R:0,G:255,B:255,A:255).
	static const Color Cyan;

	/// DarkBlue color (R:0,G:0,B:139,A:255).
	static const Color DarkBlue;

	/// DarkCyan color (R:0,G:139,B:139,A:255).
	static const Color DarkCyan;

	/// DarkGoldenrod color (R:184,G:134,B:11,A:255).
	static const Color DarkGoldenrod;

	/// DarkGray color (R:169,G:169,B:169,A:255).
	static const Color DarkGray;

	/// DarkGreen color (R:0,G:100,B:0,A:255).
	static const Color DarkGreen;

	/// DarkKhaki color (R:189,G:183,B:107,A:255).
	static const Color DarkKhaki;

	/// DarkMagenta color (R:139,G:0,B:139,A:255).
	static const Color DarkMagenta;

	/// DarkOliveGreen color (R:85,G:107,B:47,A:255).
	static const Color DarkOliveGreen;

	/// DarkOrange color (R:255,G:140,B:0,A:255).
	static const Color DarkOrange;

	/// DarkOrchid color (R:153,G:50,B:204,A:255).
	static const Color DarkOrchid;

	/// DarkRed color (R:139,G:0,B:0,A:255).
	static const Color DarkRed;

	/// DarkSalmon color (R:233,G:150,B:122,A:255).
	static const Color DarkSalmon;

	/// DarkSeaGreen color (R:143,G:188,B:139,A:255).
	static const Color DarkSeaGreen;

	/// DarkSlateBlue color (R:72,G:61,B:139,A:255).
	static const Color DarkSlateBlue;

	/// DarkSlateGray color (R:47,G:79,B:79,A:255).
	static const Color DarkSlateGray;

	/// DarkTurquoise color (R:0,G:206,B:209,A:255).
	static const Color DarkTurquoise;

	/// DarkViolet color (R:148,G:0,B:211,A:255).
	static const Color DarkViolet;

	/// DeepPink color (R:255,G:20,B:147,A:255).
	static const Color DeepPink;

	/// DeepSkyBlue color (R:0,G:191,B:255,A:255).
	static const Color DeepSkyBlue;

	/// DimGray color (R:105,G:105,B:105,A:255).
	static const Color DimGray;

	/// DodgerBlue color (R:30,G:144,B:255,A:255).
	static const Color DodgerBlue;

	/// Firebrick color (R:178,G:34,B:34,A:255).
	static const Color Firebrick;

	/// FloralWhite color (R:255,G:250,B:240,A:255).
	static const Color FloralWhite;

	/// ForestGreen color (R:34,G:139,B:34,A:255).
	static const Color ForestGreen;

	/// Fuchsia color (R:255,G:0,B:255,A:255).
	static const Color Fuchsia;

	/// Gainsboro color (R:220,G:220,B:220,A:255).
	static const Color Gainsboro;

	/// GhostWhite color (R:248,G:248,B:255,A:255).
	static const Color GhostWhite;

	/// Gold color (R:255,G:215,B:0,A:255).
	static const Color Gold;

	/// Goldenrod color (R:218,G:165,B:32,A:255).
	static const Color Goldenrod;

	/// Gray color (R:128,G:128,B:128,A:255).
	static const Color Gray;

	/// Green color (R:0,G:128,B:0,A:255).
	static const Color Green;

	/// GreenYellow color (R:173,G:255,B:47,A:255).
	static const Color GreenYellow;

	/// Honeydew color (R:240,G:255,B:240,A:255).
	static const Color Honeydew;

	/// HotPink color (R:255,G:105,B:180,A:255).
	static const Color HotPink;

	/// IndianRed color (R:205,G:92,B:92,A:255).
	static const Color IndianRed;

	/// Indigo color (R:75,G:0,B:130,A:255).
	static const Color Indigo;

	/// Ivory color (R:255,G:255,B:240,A:255).
	static const Color Ivory;

	/// Khaki color (R:240,G:230,B:140,A:255).
	static const Color Khaki;

	/// Lavender color (R:230,G:230,B:250,A:255).
	static const Color Lavender;

	/// LavenderBlush color (R:255,G:240,B:245,A:255).
	static const Color LavenderBlush;

	/// LawnGreen color (R:124,G:252,B:0,A:255).
	static const Color LawnGreen;

	/// LemonChiffon color (R:255,G:250,B:205,A:255).
	static const Color LemonChiffon;

	/// LightBlue color (R:173,G:216,B:230,A:255).
	static const Color LightBlue;

	/// LightCoral color (R:240,G:128,B:128,A:255).
	static const Color LightCoral;

	/// LightCyan color (R:224,G:255,B:255,A:255).
	static const Color LightCyan;

	/// LightGoldenrodYellow color (R:250,G:250,B:210,A:255).
	static const Color LightGoldenrodYellow;

	/// LightGray color (R:211,G:211,B:211,A:255).
	static const Color LightGray;

	/// LightGreen color (R:144,G:238,B:144,A:255).
	static const Color LightGreen;

	/// LightPink color (R:255,G:182,B:193,A:255).
	static const Color LightPink;

	/// LightSalmon color (R:255,G:160,B:122,A:255).
	static const Color LightSalmon;

	/// LightSeaGreen color (R:32,G:178,B:170,A:255).
	static const Color LightSeaGreen;

	/// LightSkyBlue color (R:135,G:206,B:250,A:255).
	static const Color LightSkyBlue;

	/// LightSlateGray color (R:119,G:136,B:153,A:255).
	static const Color LightSlateGray;

	/// LightSteelBlue color (R:176,G:196,B:222,A:255).
	static const Color LightSteelBlue;

	/// LightYellow color (R:255,G:255,B:224,A:255).
	static const Color LightYellow;

	/// Lime color (R:0,G:255,B:0,A:255).
	static const Color Lime;

	/// LimeGreen color (R:50,G:205,B:50,A:255).
	static const Color LimeGreen;

	/// Linen color (R:250,G:240,B:230,A:255).
	static const Color Linen;

	/// Magenta color (R:255,G:0,B:255,A:255).
	static const Color Magenta;

	/// Maroon color (R:128,G:0,B:0,A:255).
	static const Color Maroon;

	/// MediumAquamarine color (R:102,G:205,B:170,A:255).
	static const Color MediumAquamarine;

	/// MediumBlue color (R:0,G:0,B:205,A:255).
	static const Color MediumBlue;

	/// MediumOrchid color (R:186,G:85,B:211,A:255).
	static const Color MediumOrchid;

	/// MediumPurple color (R:147,G:112,B:219,A:255).
	static const Color MediumPurple;
	/// MediumSeaGreen color (R:60,G:179,B:113,A:255).
	static const Color MediumSeaGreen;

	/// MediumSlateBlue color (R:123,G:104,B:238,A:255).
	static const Color MediumSlateBlue;

	/// MediumSpringGreen color (R:0,G:250,B:154,A:255).
	static const Color MediumSpringGreen;

	/// MediumTurquoise color (R:72,G:209,B:204,A:255).
	static const Color MediumTurquoise;

	/// MediumVioletRed color (R:199,G:21,B:133,A:255).
	static const Color MediumVioletRed;

	/// MidnightBlue color (R:25,G:25,B:112,A:255).
	static const Color MidnightBlue;

	/// MintCream color (R:245,G:255,B:250,A:255).
	static const Color MintCream;

	/// MistyRose color (R:255,G:228,B:225,A:255).
	static const Color MistyRose;

	/// Moccasin color (R:255,G:228,B:181,A:255).
	static const Color Moccasin;

	/// NavajoWhite color (R:255,G:222,B:173,A:255).
	static const Color NavajoWhite;

	/// Navy color (R:0,G:0,B:128,A:255).
	static const Color Navy;

	/// OldLace color (R:253,G:245,B:230,A:255).
	static const Color OldLace;

	/// Olive color (R:128,G:128,B:0,A:255).
	static const Color Olive;

	/// OliveDrab color (R:107,G:142,B:35,A:255).
	static const Color OliveDrab;

	/// Orange color (R:255,G:165,B:0,A:255).
	static const Color Orange;

	/// OrangeRed color (R:255,G:69,B:0,A:255).
	static const Color OrangeRed;

	/// Orchid color (R:218,G:112,B:214,A:255).
	static const Color Orchid;

	/// PaleGoldenrod color (R:238,G:232,B:170,A:255).
	static const Color PaleGoldenrod;

	/// PaleGreen color (R:152,G:251,B:152,A:255).
	static const Color PaleGreen;

	/// PaleTurquoise color (R:175,G:238,B:238,A:255).
	static const Color PaleTurquoise;
	/// PaleVioletRed color (R:219,G:112,B:147,A:255).
	static const Color PaleVioletRed;

	/// PapayaWhip color (R:255,G:239,B:213,A:255).
	static const Color PapayaWhip;

	/// PeachPuff color (R:255,G:218,B:185,A:255).
	static const Color PeachPuff;

	/// Peru color (R:205,G:133,B:63,A:255).
	static const Color Peru;

	/// Pink color (R:255,G:192,B:203,A:255).
	static const Color Pink;

	/// Plum color (R:221,G:160,B:221,A:255).
	static const Color Plum;

	/// PowderBlue color (R:176,G:224,B:230,A:255).
	static const Color PowderBlue;

	///  Purple color (R:128,G:0,B:128,A:255).
	static const Color Purple;

	/// Red color (R:255,G:0,B:0,A:255).
	static const Color Red;

	/// RosyBrown color (R:188,G:143,B:143,A:255).
	static const Color RosyBrown;

	/// RoyalBlue color (R:65,G:105,B:225,A:255).
	static const Color RoyalBlue;

	/// SaddleBrown color (R:139,G:69,B:19,A:255).
	static const Color SaddleBrown;

	/// Salmon color (R:250,G:128,B:114,A:255).
	static const Color Salmon;

	/// SandyBrown color (R:244,G:164,B:96,A:255).
	static const Color SandyBrown;

	/// SeaGreen color (R:46,G:139,B:87,A:255).
	static const Color SeaGreen;

	/// SeaShell color (R:255,G:245,B:238,A:255).
	static const Color SeaShell;

	/// Sienna color (R:160,G:82,B:45,A:255).
	static const Color Sienna;

	/// Silver color (R:192,G:192,B:192,A:255).
	static const Color Silver;

	/// SkyBlue color (R:135,G:206,B:235,A:255).
	static const Color SkyBlue;

	/// SlateBlue color (R:106,G:90,B:205,A:255).
	static const Color SlateBlue;

	/// SlateGray color (R:112,G:128,B:144,A:255).
	static const Color SlateGray;

	/// Snow color (R:255,G:250,B:250,A:255).
	static const Color Snow;

	/// SpringGreen color (R:0,G:255,B:127,A:255).
	static const Color SpringGreen;

	/// SteelBlue color (R:70,G:130,B:180,A:255).
	static const Color SteelBlue;

	/// Tan color (R:210,G:180,B:140,A:255).
	static const Color Tan;

	/// Teal color (R:0,G:128,B:128,A:255).
	static const Color Teal;

	/// Thistle color (R:216,G:191,B:216,A:255).
	static const Color Thistle;

	/// Tomato color (R:255,G:99,B:71,A:255).
	static const Color Tomato;

	/// Turquoise color (R:64,G:224,B:208,A:255).
	static const Color Turquoise;

	/// Violet color (R:238,G:130,B:238,A:255).
	static const Color Violet;

	/// Wheat color (R:245,G:222,B:179,A:255).
	static const Color Wheat;

	/// White color (R:255,G:255,B:255,A:255).
	static const Color White;

	/// WhiteSmoke color (R:245,G:245,B:245,A:255).
	static const Color WhiteSmoke;

	/// Yellow color (R:255,G:255,B:0,A:255).
	static const Color Yellow;

	/// YellowGreen color (R:154,G:205,B:50,A:255).
	static const Color YellowGreen;
};
}
