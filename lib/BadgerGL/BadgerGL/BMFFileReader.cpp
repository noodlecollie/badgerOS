#include <cstring>
#include <cstdint>
#include <CoreUtil/BgrsAssert.h>
#include <CoreUtil/ArrayUtil.h>
#include "BMFFileReader.h"

namespace
{
	using BadgerGL::BMFFileReader;

#define LIST_ITEM(enum, desc) desc,
	static constexpr const char* const FILE_STATUS_DESCRIPTIONS[] =
	{
		BADGERGL_BMFFILEREADER_FILESTATUS_LIST
	};
#undef LIST_ITEM

	static constexpr const char BMF_SIGNATURE[4] = { 'B', 'M', 'F', 3 };

#pragma pack(push, 1)
	struct BlockIdentifier
	{
		uint8_t blockId;
		uint32_t blockLength;
	};

	struct Block_Info
	{
		static constexpr uint8_t BLOCK_ID = 1;

		int16_t fontSize;
		uint8_t isSmoothed : 1;
		uint8_t isUnicode : 1;
		uint8_t isItalic : 1;
		uint8_t isBold : 1;
		uint8_t hasFixedHeight : 1;
		uint8_t reserved : 3;
		uint8_t charSet;
		uint16_t horizontalStretch;
		uint8_t antiAliasing;
		uint8_t paddingUp;
		uint8_t paddingRight;
		uint8_t paddingDown;
		uint8_t paddingLeft;
		uint8_t spacingHorizontal;
		uint8_t spacingVertical;
		uint8_t outline;

		// Final member is the font name, but this is not included
		// in this struct because it has a variable length.
	};

	struct Block_Common
	{
		static constexpr uint8_t BLOCK_ID = 2;

		uint16_t lineHeight;
		uint16_t baseOffset;
		uint16_t widthScale;
		uint16_t heightScale;
		uint16_t numPages;
		uint8_t reserved : 7;
		uint8_t isPacked : 1;
		uint8_t alphaChannel;
		uint8_t redChannel;
		uint8_t greenChannel;
		uint8_t blueChannel;
	};

	struct Block_Character
	{
		static constexpr uint8_t BLOCK_ID = 4;

		uint32_t id;
		uint16_t x;
		uint16_t y;
		uint16_t width;
		uint16_t height;
		uint16_t xOffset;
		uint16_t yOffset;
		uint16_t xAdvance;
		uint8_t page;
		uint8_t channel;
	};
#pragma pack(pop)

	static inline bool fileHasValidSignature(const void* fileData)
	{
		return memcmp(fileData, BMF_SIGNATURE, sizeof(BMF_SIGNATURE)) == 0;
	}

	static bool validateBlockLength(const void* fileData, size_t fileLength, uint32_t& nextBlockLength)
	{
		if ( fileLength < sizeof(BlockIdentifier) )
		{
			return false;
		}

		const BlockIdentifier* identifier = static_cast<const BlockIdentifier*>(fileData);

		if ( fileLength < sizeof(BlockIdentifier) + identifier->blockLength )
		{
			return false;
		}

		nextBlockLength = identifier->blockLength;
		return true;
	}

	template<typename T>
	static BMFFileReader::FileStatus validateBlock(const void* fileData, size_t fileLength, uint32_t& nextBlockLength)
	{
		if ( !validateBlockLength(fileData, fileLength, nextBlockLength) )
		{
			return BMFFileReader::FileStatus::FileWasTooShort;
		}

		const BlockIdentifier* identifier = static_cast<const BlockIdentifier*>(fileData);

		if ( identifier->blockId != T::BLOCK_ID || identifier->blockLength < sizeof(T) )
		{
			return BMFFileReader::FileStatus::BlockDataWasNotValid;
		}

		return BMFFileReader::FileStatus::Valid;
	}

	// This assumes a valid file.
	static const Block_Character* getCharacterBlocks(const void* fileData, size_t fileLength, uint32_t& characterCount)
	{
		const uint8_t* const base = static_cast<const uint8_t*>(fileData) + sizeof(BMF_SIGNATURE);

		for ( const BlockIdentifier* identifier = reinterpret_cast<const BlockIdentifier*>(base);
			  reinterpret_cast<const uint8_t*>(identifier) - base < fileLength;
			  identifier = reinterpret_cast<const BlockIdentifier*>(reinterpret_cast<const uint8_t*>(identifier) + sizeof(BlockIdentifier) + identifier->blockLength) )
		{
			if ( identifier->blockId == Block_Character::BLOCK_ID )
			{
				characterCount = identifier->blockLength / sizeof(Block_Character);
				return reinterpret_cast<const Block_Character*>(reinterpret_cast<const uint8_t*>(identifier) + sizeof(BlockIdentifier));
			}
		}

		return nullptr;
	}
}

namespace BadgerGL
{
	const char* BMFFileReader::fileStatusDescription(FileStatus status)
	{
		const uint32_t index = static_cast<uint32_t>(status);

		return index < CoreUtil::arraySize(FILE_STATUS_DESCRIPTIONS)
			? FILE_STATUS_DESCRIPTIONS[index]
			: "<unknown>";
	}

	void BMFFileReader::setFileData(const CoreUtil::ConstBlob& data)
	{
		m_FileData = data;
		m_FileStatus = data.isValid() ? FileStatus::Unverified : FileStatus::NoFileProvided;
		m_BlockFailedValidation = 0;
	}

	void BMFFileReader::setCharInfoBuffer(BitmapMaskFont::CharInfoBuffer* buffer)
	{
		m_CharBuffer = buffer;
	}

	void BMFFileReader::populateCharInfo()
	{
		if ( !m_CharBuffer || m_FileStatus != FileStatus::Valid )
		{
			return;
		}

		uint32_t characterCount = 0;
		const Block_Character* characters = getCharacterBlocks(m_FileData.constData(), m_FileData.length(), characterCount);

		// Given we've already validated the file at this point, we expect to be able to get the data properly.
		BGRS_ASSERT(characters, "Character data was not found in validated file!");

		for ( uint32_t index = 0; index < characterCount; ++index )
		{
			const Block_Character& character = characters[index];

			uint32_t characterId = character.id;

			if ( characterId == static_cast<uint32_t>(-1) )
			{
				// Remap index -1 (invalid) to ASCII character 0, which shouldn't be used.
				characterId = 0;
			}

			if ( characterId >= m_CharBuffer->elementCount() )
			{
				continue;
			}

			BitmapMaskFont::CharInfo* charInfo = m_CharBuffer->data(characterId);
			BGRS_ASSERT(charInfo, "Character info was not valid!");

			charInfo->imageRect = BitmapMaskFont::SurfaceRect(character.x, character.y, character.x + character.width, character.y + character.height);
			charInfo->drawOffset = Point16(character.xOffset, character.yOffset);
			charInfo->advance = character.xAdvance;
		}
	}

	BMFFileReader::FileStatus BMFFileReader::validateFile()
	{
		m_BlockFailedValidation = 0;
		m_FileStatus = validateFileInternal();
		return m_FileStatus;
	}

	BMFFileReader::FileStatus BMFFileReader::fileStatus() const
	{
		return m_FileStatus;
	}

	uint8_t BMFFileReader::idOfBlockThatFailedValidation() const
	{
		return m_BlockFailedValidation;
	}

	BMFFileReader::FileStatus BMFFileReader::validateFileInternal()
	{
		if ( !m_FileData.isValid() )
		{
			return FileStatus::NoFileProvided;
		}

		if ( m_FileData.length() < sizeof(BMF_SIGNATURE) )
		{
			return FileStatus::FileWasTooShort;
		}

		if ( !fileHasValidSignature(m_FileData.constData()) )
		{
			return FileStatus::FileWasNotBMF;
		}

		// The following is a bit scruffy, but should serve its purpose for now.
		const uint8_t* fileData = m_FileData.constBytes() + sizeof(BMF_SIGNATURE);
		size_t fileLength = m_FileData.length() - sizeof(BMF_SIGNATURE);

		FileStatus status = validateInfoBlock(fileData, fileLength);

		if ( status != FileStatus::Valid )
		{
			m_BlockFailedValidation = Block_Info::BLOCK_ID;
			return status;
		}

		status = validateCommonBlock(fileData, fileLength);

		if ( status != FileStatus::Valid )
		{
			m_BlockFailedValidation = Block_Common::BLOCK_ID;
			return status;
		}

		status = validatePagesBlock(fileData, fileLength);

		if ( status != FileStatus::Valid )
		{
			m_BlockFailedValidation = 3;
			return status;
		}

		status = validateCharactersBlock(fileData, fileLength);

		if ( status != FileStatus::Valid )
		{
			m_BlockFailedValidation = Block_Character::BLOCK_ID;
			return status;
		}

		status = validateKerningPairsBlock(fileData, fileLength);

		if ( status != FileStatus::Valid )
		{
			m_BlockFailedValidation = 5;
		}

		return status;
	}

	BMFFileReader::FileStatus BMFFileReader::validateInfoBlock(const uint8_t*& fileData, size_t& fileLength)
	{
		uint32_t blockLength = 0;
		FileStatus status = validateBlock<Block_Info>(fileData, fileLength, blockLength);

		if ( status != FileStatus::Valid )
		{
			return status;
		}

		const char* const fontName = reinterpret_cast<const char*>(fileData) + sizeof(BlockIdentifier) + sizeof(Block_Info);
		const size_t fontNameLength = blockLength - sizeof(Block_Info);

		// Make sure the last character of the font name is terminated.
		if ( fontName[fontNameLength - 1] != '\0' )
		{
			return FileStatus::BlockDataWasNotValid;
		}

		fileData += sizeof(BlockIdentifier) + blockLength;
		fileLength -= sizeof(BlockIdentifier) + blockLength;
		return FileStatus::Valid;
	}

	BMFFileReader::FileStatus BMFFileReader::validateCommonBlock(const uint8_t*& fileData, size_t& fileLength)
	{
		uint32_t blockLength = 0;
		FileStatus status = validateBlock<Block_Common>(fileData, fileLength, blockLength);

		if ( status != FileStatus::Valid )
		{
			return status;
		}

		fileData += sizeof(BlockIdentifier) + blockLength;
		fileLength -= sizeof(BlockIdentifier) + blockLength;
		return FileStatus::Valid;
	}

	BMFFileReader::FileStatus BMFFileReader::validatePagesBlock(const uint8_t*& fileData, size_t& fileLength)
	{
		uint32_t blockLength = 0;

		if ( !validateBlockLength(fileData, fileLength, blockLength) )
		{
			return FileStatus::FileWasTooShort;
		}

		// Don't bother doing validation on the contents of this block, since we
		// don't support its use at the moment.

		fileData += sizeof(BlockIdentifier) + blockLength;
		fileLength -= sizeof(BlockIdentifier) + blockLength;
		return FileStatus::Valid;
	}

	BMFFileReader::FileStatus BMFFileReader::validateCharactersBlock(const uint8_t*& fileData, size_t& fileLength)
	{
		uint32_t blockLength = 0;
		FileStatus status = validateBlock<Block_Character>(fileData, fileLength, blockLength);

		if ( status != FileStatus::Valid )
		{
			return status;
		}

		// Make sure that the block length is a multiple of the individual character block length.
		if ( blockLength % sizeof(Block_Character) != 0 )
		{
			return FileStatus::BlockDataWasNotValid;
		}

		fileData += sizeof(BlockIdentifier) + blockLength;
		fileLength -= sizeof(BlockIdentifier) + blockLength;
		return FileStatus::Valid;
	}

	BMFFileReader::FileStatus BMFFileReader::validateKerningPairsBlock(const uint8_t*& fileData, size_t& fileLength)
	{
		// These are optional, so don't check if we're out of file data.
		if ( fileLength < 1 )
		{
			return FileStatus::Valid;
		}

		uint32_t blockLength = 0;

		if ( !validateBlockLength(fileData, fileLength, blockLength) )
		{
			return FileStatus::FileWasTooShort;
		}

		// Don't bother doing validation on the contents of this block, since we
		// don't support its use at the moment.

		fileData += sizeof(BlockIdentifier) + blockLength;
		fileLength -= sizeof(BlockIdentifier) + blockLength;
		return FileStatus::Valid;
	}
}
