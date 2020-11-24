#include <cstring>
#include <cstdint>
#include <CoreUtil/BgrsAssert.h>
#include <CoreUtil/ArrayUtil.h>
#include <BadgerUI/BMFFileReader.h>

// TODO: This whole file could do with a good refactor.

namespace
{
	using BadgerUI::BMFFileReader;

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
}

namespace BadgerUI
{
	const char* BMFFileReader::fileStatusDescription(FileStatus status)
	{
		const uint32_t index = static_cast<uint32_t>(status);

		return index < CoreUtil::arraySize(FILE_STATUS_DESCRIPTIONS)
			? FILE_STATUS_DESCRIPTIONS[index]
			: "<unknown>";
	}

	BMFFileReader::BMFFileReader()
	{
		clearBlockOffsets();
	}

	void BMFFileReader::setFileData(const CoreUtil::ConstBlob& data)
	{
		m_FileData = data;
		m_FileStatus = data.isValid() ? FileStatus::Unverified : FileStatus::NoFileProvided;
		m_BlockFailedValidation = 0;
		clearBlockOffsets();
	}

	void BMFFileReader::setCharGroupContainer(BadgerGL::FontCharacterGroupContainer* container)
	{
		m_CharGroupContainer = container;
	}

	void BMFFileReader::populateCharInfo()
	{
		if ( !m_CharGroupContainer || m_FileStatus != FileStatus::Valid )
		{
			return;
		}

		const uint8_t* const base = m_FileData.constBytes() + m_BlockOffsets[Block_Character::BLOCK_ID];
		const Block_Character* characters = reinterpret_cast<const Block_Character*>(base);
		uint32_t characterCount = (reinterpret_cast<const BlockIdentifier*>(base - sizeof(BlockIdentifier))->blockLength) / sizeof(Block_Character);

		for ( uint32_t index = 0; index < characterCount; ++index )
		{
			const Block_Character& character = characters[index];

			uint32_t characterId = character.id;

			if ( characterId == static_cast<uint32_t>(-1) )
			{
				// Remap index -1 (invalid) to ASCII character 0, which shouldn't be used.
				characterId = 0;
			}

			BadgerGL::FontCharacterInfo* charInfo = m_CharGroupContainer->charInfo(characterId);

			if ( !charInfo )
			{
				// Character not supported by font.
				continue;
			}

			charInfo->imageRect = BadgerGL::BitmapMask::SurfaceRect(character.x, character.y, character.x + character.width, character.y + character.height);
			charInfo->drawOffset = BadgerGL::Point16(character.xOffset, character.yOffset);
			charInfo->advance = character.xAdvance;
		}
	}

	uint16_t BMFFileReader::lineHeight() const
	{
		if ( m_FileStatus != FileStatus::Valid )
		{
			return 0;
		}

		const uint8_t* const base = m_FileData.constBytes() + m_BlockOffsets[Block_Common::BLOCK_ID];
		return reinterpret_cast<const Block_Common*>(base)->lineHeight;
	}

	BMFFileReader::FileStatus BMFFileReader::validateFile()
	{
		m_BlockFailedValidation = 0;
		m_FileStatus = validateFileInternal();

		if ( m_FileStatus != FileStatus::Valid )
		{
			clearBlockOffsets();
		}

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

		m_BlockOffsets[Block_Info::BLOCK_ID] = (fileData + sizeof(BlockIdentifier)) - m_FileData.constBytes();

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

		m_BlockOffsets[Block_Common::BLOCK_ID] = (fileData + sizeof(BlockIdentifier)) - m_FileData.constBytes();

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

		m_BlockOffsets[Block_Character::BLOCK_ID] = (fileData + sizeof(BlockIdentifier)) - m_FileData.constBytes();

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

	void BMFFileReader::clearBlockOffsets()
	{
		memset(m_BlockOffsets, 0, sizeof(m_BlockOffsets));
	}
}
