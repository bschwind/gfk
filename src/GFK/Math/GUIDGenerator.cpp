#include <GFK/Math/GUIDGenerator.hpp>
#include <GFK/OSDetection.hpp>

#if defined(PLATFORM_WINDOWS)
	#include <Rpc.h>
	#pragma comment(lib, "Rpcrt4.lib")
#else
	#include <uuid/uuid.h>
#endif

namespace gfk
{

// Generates a 128-bit GUID
std::string GUIDGenerator::GenerateGUID()
{
#if defined(PLATFORM_WINDOWS)
	UUID uuid;
	UuidCreate(&uuid);

	unsigned char *str;
	UuidToStringA (&uuid, &str);

	std::string s((char*) str);

	RpcStringFreeA(&str);
#else
	uuid_t uuid;
	uuid_generate_random(uuid);
	char s[39];
	uuid_unparse(uuid, s);
#endif
	return s;
}


}
