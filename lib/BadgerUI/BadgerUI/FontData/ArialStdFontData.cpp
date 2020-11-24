#include <BadgerUI/FontData/ArialStdFontData.h>

namespace BadgerUI
{
	ArialStdFontData* ArialStdFontData::StaticInstance()
	{
		static ArialStdFontData instance;
		return &instance;
	}
}
