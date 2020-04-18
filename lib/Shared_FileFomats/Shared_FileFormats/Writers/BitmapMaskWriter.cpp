#include <cstring>
#include <BadgerGL/Defs.h>
#include "BitmapMaskWriter.h"
#include "../BitmapMask.h"

namespace FileFormats
{
	namespace BitmapMask
	{
		bool write(const FileWriter& writer, uint16_t width, uint16_t height, const void* data, size_t dataLength)
		{
			if ( !writer.write || !data )
			{
				return false;
			}

			const size_t fileDataSize = BadgerGL::maskedDataSizeForDimensions(width, height);

			if ( dataLength < fileDataSize )
			{
				return false;
			}

			Header header;
			memset(&header, 0, sizeof(header));

			header.signature = Header::SIGNATURE;
			header.width = width;
			header.height = height;

			return writer.write(&header, sizeof(header), writer.userData) &&
				   writer.write(data, fileDataSize, writer.userData);
		}
	}
}
