#pragma once

#include <CoreUtil/Blob.h>
#include <BadgerGL/FontCharacterGroupContainer.h>

namespace BadgerUI
{
#define BADGERGL_BMFFILEREADER_FILESTATUS_LIST \
	LIST_ITEM(Valid = 0, "Valid") \
	LIST_ITEM(Unverified, "File not verified yet") \
	LIST_ITEM(NoFileProvided, "No file was provided") \
	LIST_ITEM(FileWasTooShort, "File was too short to contain required data") \
	LIST_ITEM(FileWasNotBMF, "File was not a BMF file") \
	LIST_ITEM(BlockDataWasNotValid, "Invalid block data was encountered")

	// TODO: Architecture of this class is kinda messy. Block structs should probably be
	// forward-declared privately, and functions taking references to data and length
	// should be refactored to be better.
	class BMFFileReader
	{
	public:
#define LIST_ITEM(enum, desc) enum,
		enum class FileStatus
		{
			BADGERGL_BMFFILEREADER_FILESTATUS_LIST
		};
#undef LIST_ITEM

		static const char* fileStatusDescription(FileStatus status);

		BMFFileReader();

		void setFileData(const CoreUtil::ConstBlob& data);
		void setCharGroupContainer(BadgerGL::FontCharacterGroupContainer* container);

		FileStatus validateFile();

		// Returns the results of the last validateFile() call
		// for the provided file. If validateFile() has not yet
		// been called on a new file, this will return Unverified.
		FileStatus fileStatus() const;
		uint8_t idOfBlockThatFailedValidation() const;

		// If the target char buffer object has not been set, or fileStatus()
		// is not valid, this function does nothing.
		void populateCharInfo();

		uint16_t lineHeight() const;

	private:
		static constexpr size_t MAX_BLOCKS = 5;

		uint m_BlockOffsets[MAX_BLOCKS];

		void clearBlockOffsets();
		FileStatus validateFileInternal();

		FileStatus validateInfoBlock(const uint8_t*& fileData, size_t& fileLength);
		FileStatus validateCommonBlock(const uint8_t*& fileData, size_t& fileLength);
		FileStatus validatePagesBlock(const uint8_t*& fileData, size_t& fileLength);
		FileStatus validateCharactersBlock(const uint8_t*& fileData, size_t& fileLength);
		FileStatus validateKerningPairsBlock(const uint8_t*& fileData, size_t& fileLength);

		CoreUtil::ConstBlob m_FileData;
		FileStatus m_FileStatus = FileStatus::NoFileProvided;
		uint8_t m_BlockFailedValidation = 0;
		BadgerGL::FontCharacterGroupContainer* m_CharGroupContainer = nullptr;

		uint32_t m_CharactersBlockOffset = 0;
		uint32_t m_CommonBlockOffset = 0;
	};
}
