import argparse
import os
import math
import re
from PIL import Image

# The Heltec OLED binary image format is row-major, where the Y position of each column increases as
# you go from the LSB to the MSB of each byte. If the Y dimension of the image is not a multiple of
# 8, the rest of the byte after the last pixel in the column is treated as padding and is ignored.
# For a WxH image, there are W columns of ceil(H/8) bytes laid out sequentially in memory.

def parseArgs():
	parser = argparse.ArgumentParser("ssd1306-image-convert",
									 description="Converts an image to the BadgeOS OLED-specific bitmap format.")

	parser.add_argument("-i", "--input",
						required=True,
						help="Input file.")

	parser.add_argument("-o", "--output",
						required=True,
						help="Output header file.")

	return parser.parse_args()

def loadImage(imagePath):
	print("Loading image:", imagePath)

	if not os.path.isfile(imagePath):
		raise OSError(f"Image {imagePath} is not a valid file.")

	return Image.open(imagePath).convert(mode="1")

def alignToMultipleOfEight(num):
	return 8 * math.ceil(num/8)

def convertImageData(img):
	(width, height) = img.size
	alignedHeight = alignToMultipleOfEight(height)

	print("Image size:", f"{width}x{height}")
	print("Byte-aligned height:", alignedHeight)

	imgData = [0] * (width * alignedHeight)

	# Ensure that data is in column-major order.
	for x in range(0, width):
		for y in range(0, height):
			imgData[(x * alignedHeight) + y] = int(img.getpixel((x, y)) / 255)

	return (width, height, imgData)

def packImageData(data):
	outData = [0] * int(len(data) / 8)
	print("Image requires", len(outData), "bytes of packed data.")

	for byteIndex in range(0, len(outData)):
		bitIndex = byteIndex * 8
		bits = data[bitIndex : bitIndex + 8]
		outValue = 0

		for i in range(0, len(bits)):
			if bits[i]:
				outValue = outValue | (1 << i)

		outData[byteIndex] = outValue

	return outData

def writeHeader(path, width, height, data):
	print("Writing packed data to:", path)

	baseName = os.path.basename(path)
	(fileName, _) = os.path.splitext(baseName)
	sanitisedFileName = re.sub(r"[^A-Za-z0-9_]", "", fileName)

	preLines = \
	[
		"#pragma once\n",
		"\n",
		"// Header generated by ssd1306-image-convert.py\n",
		f"// Size: {width}x{height} ({len(data)} bytes including padding).\n",
		"\n",
		"#include <cstdint>\n",
		"#include <cstddef>\n",
		"\n",
		f"namespace Image_{sanitisedFileName}\n",
		"{\n",
		f"\tstatic constexpr size_t WIDTH = {width};\n",
		f"\tstatic constexpr size_t HEIGHT = {height};\n",
		f"\tstatic constexpr const uint8_t DATA[] =\n",
		"\t{\n"
	]

	dataLines = []

	postLines = \
	[
		"\t};\n",
		"}\n"
	]

	for i in range(0, len(data)):
		line = ""

		if i == 0:
			# First line, so provide indent.
			line += "\t\t"
		elif (i % 8) == 0:
			# Need comma, new line + indent.
			line += ",\n\t\t"
		else:
			# Need comma only.
			line += ", "

		value = data[i]
		line += f"{value:#04x}"

		if i == len(data) - 1:
			line += "\n"

		dataLines.append(line)

	with open(path, "w") as outFile:
		for line in preLines:
			outFile.write(line)

		for line in dataLines:
			outFile.write(line)

		for line in postLines:
			outFile.write(line)

	print("Complete.")

def main():
	args = parseArgs()

	img = loadImage(args.input)
	(width, height, imgData) = convertImageData(img)
	packedData = packImageData(imgData)

	writeHeader(args.output, width, height, packedData)

if __name__ == "__main__":
	main()
