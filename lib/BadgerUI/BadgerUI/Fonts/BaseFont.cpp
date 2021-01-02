#include <BadgerUI/Fonts/BaseFont.h>
#include <BadgerUI/BMFFileReader.h>

namespace BadgerUI
{
	namespace Fonts
	{
		void BaseFont::initialise()
		{
			BMFFileReader reader;

			reader.setCharGroupContainer(&m_CharGroupContainer);
			reader.setFileData(m_BMFData);

			const BMFFileReader::FileStatus status = reader.validateFile();

			if ( status != BMFFileReader::FileStatus::Valid )
			{
				return;
			}

			reader.populateCharInfo();

			setLineHeight(reader.lineHeight());
			setCharContainer(&m_CharGroupContainer);
			setFontBitmap(m_FontBitmap);
		}
	}
}
