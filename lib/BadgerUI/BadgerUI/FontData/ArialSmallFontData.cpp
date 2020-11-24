#include <BadgerUI/FontData/ArialSmallFontData.h>

namespace BadgerUI
{
	ArialSmallFontData* ArialSmallFontData::StaticInstance()
	{
		static ArialSmallFontData instance;
		return &instance;
	}
}
