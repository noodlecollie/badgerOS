#pragma once

#include <cstdint>

#ifndef VERSION_NUMBER_MAJOR
#ifdef BGRS_DEBUG
#define VERSION_NUMBER_MAJOR 0
#else
#error No major version number defined.
#endif
#endif // VERSION_NUMBER_MAJOR

#ifndef VERSION_NUMBER_MINOR
#ifdef BGRS_DEBUG
#define VERSION_NUMBER_MINOR 0
#else
#error No minor version number defined.
#endif
#endif // VERSION_NUMBER_MINOR

// The build hash should always be defined, since it is generated automatically.
#ifndef BUILD_HASH
#error No build hash defined.
#endif

namespace PlatformConfig
{
	namespace Versions
	{
#define TOSTR(x) TOSTR2(x)
#define TOSTR2(x) #x

		static constexpr const char* VERSION_STRING = TOSTR(VERSION_NUMBER_MAJOR) "." TOSTR(VERSION_NUMBER_MINOR);
		static constexpr const char* VERSION_STRING_FULL = TOSTR(VERSION_NUMBER_MAJOR) "." TOSTR(VERSION_NUMBER_MINOR) "." TOSTR(BUILD_HASH);

		static constexpr uint32_t VERSION_MAJOR = VERSION_NUMBER_MAJOR;
		static constexpr const char* VERSION_MAJOR_STRING = TOSTR(VERSION_NUMBER_MAJOR);

		static constexpr uint32_t VERSION_MINOR = VERSION_NUMBER_MINOR;
		static constexpr const char* VERSION_MINOR_STRING = TOSTR(VERSION_NUMBER_MINOR);

		static constexpr const char* VERSION_BUILD_HASH_STRING = TOSTR(BUILD_HASH);

#undef TOSTR
#undef TOSTR2
	}
}
