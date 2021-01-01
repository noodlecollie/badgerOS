#include <Arduino.h>
#include <BadgerUI/FontData/BaseFontData.h>
#include <BadgerUI/BMFFileReader.h>

namespace BadgerUI
{
	bool BaseFontData::isValid() const
	{
		return m_FontObject.isValid();
	}

	const BadgerGL::BitmapMask* BaseFontData::fontBitmap() const
	{
		return m_FontBitmap;
	}

	void BaseFontData::setFontBitmap(const BadgerGL::BitmapMask* bitmap)
	{
		m_FontBitmap = bitmap;
		m_FontObject.setFontBitmap(m_FontBitmap);
	}

	const CoreUtil::ConstBlob& BaseFontData::bmfData() const
	{
		return m_BMFData;
	}

	void BaseFontData::setBMFData(const CoreUtil::ConstBlob& data)
	{
		m_BMFData = data;
	}

	const BadgerGL::BitmapMaskFont& BaseFontData::fontObject() const
	{
		return m_FontObject;
	}

	bool BaseFontData::initialise()
	{
		BMFFileReader reader;

		reader.setCharGroupContainer(this);
		reader.setFileData(bmfData());

		const BMFFileReader::FileStatus status = reader.validateFile();

		if ( status != BMFFileReader::FileStatus::Valid )
		{
			const uint8_t block = reader.idOfBlockThatFailedValidation();
			const char* const description = BMFFileReader::fileStatusDescription(status);

			Serial.printf("Font failed to load. Error: %s. (Faulty block ID: %u)\r\n", description, block);
			return false;
		}

		reader.populateCharInfo();

		m_FontObject.setLineHeight(reader.lineHeight());
		m_FontObject.setCharContainer(this);
		m_FontObject.setFontBitmap(m_FontBitmap);

		return m_FontObject.isValid();
	}
}
