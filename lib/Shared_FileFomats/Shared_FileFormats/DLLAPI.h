#pragma once

#ifdef WIN32

// The following is defined automatically by Visual Studio.
#ifdef FILEFORMATSLIB_EXPORTS
#define FILEFORMATSLIB_API __declspec(dllexport)
#else // FILEFORMATSLIB_EXPORTS
#define FILEFORMATSLIB_API __declspec(dllimport)
#endif // FILEFORMATSLIB_EXPORTS

#else // WIN32

#define FILEFORMATSLIB_API

#endif // WIN32
