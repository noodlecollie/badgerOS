import sys
import os
import argparse
import subprocess

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
ROOT_DIR = os.path.realpath(os.path.join(SCRIPT_DIR, "..", ".."))
FONT_HEADER_OUTPUT_DIR = os.path.join(ROOT_DIR, "lib", "Resources", "Resources", "Fonts")
BITMAP_HEADER_OUTPUT_DIR = os.path.join(ROOT_DIR, "lib", "Resources", "Resources", "Images")

INTERPRETER_PATH = sys.executable
IMAGECONVERT_PATH = os.path.join(ROOT_DIR, "xamarin", "BadgerApp", "ImageConvert", "bin", "release", "ImageConvert.exe")
TRIMMER_PATH = os.path.join(ROOT_DIR, "utils", "bitmapfonttrimmer", "bitmapfonttrimmer.py")

class FontFileConfig:
	def __init__(self, fontName : str):
		self.fontName = fontName
		self.fontDir = os.path.join(SCRIPT_DIR, fontName)
		self.fntFile = None
		self.trimmedFntFile = None
		self.pngFile = None
		self.fontHeader = None
		self.bitmapHeader = None

def __parseArgs():
	parser = argparse.ArgumentParser("compilefont",
									 description="Compiles headers to use a bitmap font in code.")

	parser.add_argument("fontname",
						help="Subdirectory within assets/fonts containing font files.")

	return parser.parse_args()

def __runProcess(args):
	print("Running command:", *args)

	result = subprocess.run(args)

	if result.returncode != 0:
		print("Command", *args, "returned error code", result.returncode, file=sys.stderr)
		sys.exit(1)

	print("Command", *args, "completed successfully.")

def __dataToCArray(inData : bytes, bytesPerLine : int = 8, indent : str = ""):
	dataLines = []
	line = ""

	for i in range(0, len(inData)):
		if (i % bytesPerLine) == 0:
			# New line started - commit previous line.
			if line:
				line += ","
				dataLines.append(line)
				line = ""

			line += indent
		else:
			# Continuation of previous line
			line += ", "

		value = inData[i]
		line += f"{value:#04x}"

	if line:
		dataLines.append(line)

	return "\n".join(dataLines)

def __fontHeaderData(config):
	fontData = []

	with open(config.trimmedFntFile, "rb") as inFile:
		fontData = inFile.read()

	preLines = \
	[
		"#pragma once",
		"",
		f"// Created using: compilefont.py {config.fontName}",
		"",
		"#include <cstdint>",
		"#include <cstddef>",
		"#include <CoreUtil/Blob.h>",
		"",
		"namespace Resources",
		"{",
		f"\tnamespace {config.fontName}Font",
		"\t{",
		f"\t\tstatic constexpr size_t LENGTH = {len(fontData)};",
		"\t\tstatic constexpr uint8_t DATA[LENGTH] =",
		"\t\t{"
	]

	dataLines = __dataToCArray(fontData, 8, "\t\t\t")

	postLines = \
	[
		"\t\t};",
		"",
		"\t\tstatic constexpr CoreUtil::ConstBlob BLOB(DATA, LENGTH);",
		"\t}",
		"}"
	]

	# Python automatically translates \n to \r\n when writing text files.
	return "\n".join(preLines) + "\n" + dataLines + "\n" + "\n".join(postLines)

def __getFontFileConfig(fontName):
	config = FontFileConfig(fontName)

	if not os.path.isdir(config.fontDir):
		print("Directory", config.fontDir, "does not exist.", file=sys.stderr)

	for fileName in os.listdir(config.fontDir):
		fullPath = os.path.join(config.fontDir, fileName)
		name, ext = os.path.splitext(fileName)

		if ext == ".png":
			if config.pngFile is not None:
				print("Found more than one PNG file in directory", config.fontDir, "-", config.pngFile, "and", fullPath, file=sys.stderr)
				sys.exit(1)

			config.pngFile = fullPath
		elif ext == ".fnt" and not name.endswith("_trimmed"):
			if config.fntFile is not None:
				print("Found more than one FNT file in directory", config.fontDir, "-", config.fntFile, "and", fullPath, file=sys.stderr)
				sys.exit(1)

			config.fntFile = fullPath

	if config.pngFile is None:
		print("Could not find any PNG files in", config.fontDir, file=sys.stderr)
		sys.exit(1)

	if config.fntFile is None:
		print("Could not find any FNT files in", config.fontDir, file=sys.stderr)
		sys.exit(1)

	config.fontHeader = os.path.join(FONT_HEADER_OUTPUT_DIR, config.fontName + "Font.h")
	config.bitmapHeader = os.path.join(BITMAP_HEADER_OUTPUT_DIR, config.fontName + "Bitmap.h")

	print("Compiling font files for:", config.fontDir)
	return config

def __trimFont(config):
	print("Trimming font:", config.fntFile)

	fileName, fileExt = os.path.splitext(config.fntFile)
	fileName += "_trimmed"
	outputFilePath = fileName + fileExt

	args = \
	[
		INTERPRETER_PATH,
		TRIMMER_PATH,
		"-i",
		config.fntFile,
		"-o",
		outputFilePath
	]

	__runProcess(args)
	config.trimmedFntFile = outputFilePath

def __fntFileToHeader(config):
	print("Writing font header:", config.fontHeader)

	with open(config.fontHeader, "w") as outFile:
		outFile.write(__fontHeaderData(config))

def __pngFileToHeader(config):
	print("Writing bitmap header:", config.bitmapHeader)

	args = \
	[
		IMAGECONVERT_PATH,
		"toheader",
		"--namespace",
		"Resources",
		"--bitmap-name",
		f"{config.fontName}Bitmap",
		"-i",
		config.pngFile,
		"-o",
		config.bitmapHeader,
		"-f",
		"BitmapMask"
	]

	__runProcess(args)

def __main():
	if sys.platform != "win32":
		# We can only run on Windows right now because we depend on the ImageConvert utility.
		print("This script is currently only supported on Windows.", file=sys.stderr)
		sys.exit(1)

	if not os.path.isfile(IMAGECONVERT_PATH):
		print(IMAGECONVERT_PATH, "was not found. Please ensure the utility is compiled.", file=sys.stderr)
		sys.exit(1)

	args = __parseArgs()
	config = __getFontFileConfig(args.fontname)

	__trimFont(config)
	__fntFileToHeader(config)
	__pngFileToHeader(config)

	print("Done.")

if __name__ == "__main__":
	__main()
