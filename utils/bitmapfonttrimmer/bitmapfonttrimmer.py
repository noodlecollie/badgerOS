import argparse
import sys
import struct

# This script is kinda rough and ready, and does not do a lot of file structure validity checking. Sorry.

FILE_SIGNATURE = b"BMF\x03"
FIRST_BLOCK_IDENT_INDEX = len(FILE_SIGNATURE)

FORMAT_BLOCK_IDENT = "=BI"
BLOCK_IDENT_STRUCT_SIZE = struct.calcsize(FORMAT_BLOCK_IDENT)

FORMAT_BLOCK_CHAR = "=IHHHHhhhBB"
BLOCK_CHAR_STRUCT_SIZE = struct.calcsize(FORMAT_BLOCK_CHAR)
YOFFSET_ITEM_OFFSET = 14

BLOCK_ID_INFO = 1
BLOCK_ID_COMMON = 2
BLOCK_ID_CHARACTERS = 4

def parseArgs():
	parser = argparse.ArgumentParser("bitmapfonttrimmer",
									 description="Removes line spacing in binary bitmap font files, "+
									 			 "so that characters are drawn flush against the top of " +
												 "their allotted area of the screen.")

	parser.add_argument("-i", "--input",
						required=True,
						help="Input file.")

	parser.add_argument("-o", "--output",
						required=True,
						help="Output file.")

	return parser.parse_args()

def fileIsBMF(contents):
	return len(contents) >= 4 and bytes(contents[0:len(FILE_SIGNATURE)]) == FILE_SIGNATURE

def findBlockOffsetAndSize(contents, id):
	index = FIRST_BLOCK_IDENT_INDEX

	while index < len(contents):
		identifier = struct.unpack_from(FORMAT_BLOCK_IDENT, contents, index)

		if identifier[0] == id:
			return (index + BLOCK_IDENT_STRUCT_SIZE, identifier[1])

		index += BLOCK_IDENT_STRUCT_SIZE + identifier[1]

	raise Exception(f"Could not find block with ID {id}")

def getFontSize(contents):
	offset, _ = findBlockOffsetAndSize(contents, BLOCK_ID_INFO)
	fontSize = struct.unpack_from("=h", contents, offset)[0]

	if fontSize < 0:
		# Used to specify that the font height should match the char height.
		# We don't care - just invert to get the real value.
		fontSize *= -1

	return fontSize

def getLineHeight(contents):
	offset, _ = findBlockOffsetAndSize(contents, BLOCK_ID_COMMON)
	return struct.unpack_from("=H", contents, offset)[0]

def trimAllCharOffsets(contents, outContents, yDelta):
	offset, size = findBlockOffsetAndSize(contents, BLOCK_ID_CHARACTERS)
	print(f"Chars block at file offset {offset}, size {size}")

	for itemOffset in range(offset, offset + size, BLOCK_CHAR_STRUCT_SIZE):
		charInfo = struct.unpack_from(FORMAT_BLOCK_CHAR, contents, itemOffset)
		yOffset = charInfo[6]
		yOffset += yDelta

		print("Char", chr(charInfo[0]) if charInfo[0] < 0x10FFFF else "<invalid>", "Y offset is now", yOffset)

		toWrite = tuple(charInfo[0:6] + (yOffset,) + charInfo[7:])
		packedData = struct.pack(FORMAT_BLOCK_CHAR, *toWrite)

		for subIndex in range(0, len(packedData)):
			outContents[itemOffset + subIndex] = packedData[subIndex]

def setLineHeight(contents, outContents, height):
	offset, _ = findBlockOffsetAndSize(contents, BLOCK_ID_COMMON)
	packedData = struct.pack("=H", height)

	for subIndex in range(0, len(packedData)):
			outContents[offset + subIndex] = packedData[subIndex]

def main():
	args = parseArgs()
	fileContents = []

	with open(args.input, "rb") as inFile:
		fileContents = inFile.read()

	print("Read file:", args.input, f"({len(fileContents)} bytes)")

	if not fileIsBMF(fileContents):
		print("Input file was not a valid bitmap font binary descriptor.", file=sys.stderr)
		sys.exit(1)

	fontSize = getFontSize(fileContents)
	print("Font target size is", fontSize)

	lineHeight = getLineHeight(fileContents)
	print("Font line height is", lineHeight)

	if lineHeight <= fontSize:
		print("No need to trim line height, exiting.")
		sys.exit(0)

	heightToTrim = lineHeight - fontSize
	print("Trimming", heightToTrim, "pixels from all character offsets.")

	outContents = list(fileContents)
	trimAllCharOffsets(fileContents, outContents, -heightToTrim)
	setLineHeight(fileContents, outContents, fontSize)

	print("Writing:", args.output)

	with open(args.output, "wb") as outFile:
		outFile.write(bytes(outContents))

	print("Done.")

if __name__ == "__main__":
	main()
