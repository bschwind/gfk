#if defined(_WIN32) || defined(__WIN32__)
	// Windows
	#define PLATFORM_WINDOWS
	typedef __int32 int32_t;
	typedef unsigned __int32 uint32_t;
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
		// iOS
		#define PLATFORM_IOS
		#define PLATFORM_MOBILE
	#else
		// MacOS
		#define PLATFORM_MAC
	#endif
#elif defined(__ANDROID__)
	// Android
	#define PLATFORM_ANDROID
	#define PLATFORM_MOBILE
#else
	// *nix
	#define PLATFORM_UNIX
#endif
