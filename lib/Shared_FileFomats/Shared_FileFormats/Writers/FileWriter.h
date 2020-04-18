#pragma once

#include <cstddef>
#include <CoreUtil/CallingConventions.h>

namespace FileFormats
{
	struct FileWriter
	{
		void* userData;

		size_t (BGRS_STDCALL * write)(const void* data, size_t length, void* usrData);
	};
}
