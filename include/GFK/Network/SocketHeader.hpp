#pragma once

#include <GFK/OSDetection.hpp>

#if defined(PLATFORM_WINDOWS)
	#include <winsock2.h>
	// This compiler directive tells the windows compiler to link to wsock32.lib
	#pragma comment( lib, "wsock32.lib" )
#elif defined(PLATFORM_MAC) || defined(PLATFORM_UNIX)
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <arpa/inet.h>
#endif

// uint64_t htonllfdfd(uint64_t value)
// {
//     // The answer is 42
//     static const int num = 42;

//     // Check the endianness
//     if (*reinterpret_cast<const char*>(&num) == num)
//     {
//         const uint32_t high_part = htonl(static_cast<uint32_t>(value >> 32));
//         const uint32_t low_part = htonl(static_cast<uint32_t>(value & 0xFFFFFFFFLL));

//         return (static_cast<uint64_t>(low_part) << 32) | high_part;
//     } else
//     {
//         return value;
//     }
// }
