import argparse
import os
import math
import re

def parseArgs():
	parser = argparse.ArgumentParser("filetoheader",
									 description="Converts a binary file to a C++ header of raw bytes.")

	parser.add_argument("-i", "--input",
						required=True,
						help="Input file.")

	parser.add_argument("-o", "--output",
						required=True,
						help="Output header file.")

	parser.add_argument("-n", "--namespace",
						required=True,
						help="Name of namespace within which to place the header data.")

	return parser.parse_args()

def createHeaderFileContent(inData, namespace):
	preLines = \
	[
		"#pragma once\n",
		"\n",
		"#include <cstdint>\n",
		"#include <cstddef>\n",
		"\n",
		f"namespace {namespace}\n",
		"{\n",
		f"\tstatic constexpr size_t LENGTH = {len(inData)};\n",
		"\tstatic constexpr uint8_t DATA[LENGTH] =\n",
		"\t{\n"
	]

	dataLines = []

	for i in range(0, len(inData)):
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

		value = inData[i]
		line += f"{value:#04x}"

		if i == len(inData) - 1:
			line += "\n"

		dataLines.append(line)

	postLines = \
	[
		"\t};\n",
		"}\n"
	]

	return "".join(preLines + dataLines + postLines)

def main():
	args = parseArgs()
	fileContent = []

	with open(args.input, "rb") as inFile:
		fileContent = inFile.read()

	print("Read file:", args.input, f"({len(fileContent)} bytes)")

	outData = createHeaderFileContent(fileContent, args.namespace)

	print("Writing header:", args.output)
	with open(args.output, "w") as outFile:
		outFile.write(outData)

	print("Done.")

if __name__ == "__main__":
	main()
