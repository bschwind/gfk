#if defined(_WIN32) || defined(__WIN32__)
	// Windows
	#define PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
	// MacOS
	#define PLATFORM_MAC
#elif defined(__ANDROID__)
	// Android
	#define PLATFORM_ANDROID
#else
	// *nix
	#define PLATFORM_UNIX
#endif