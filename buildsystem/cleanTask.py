import os

from . import buildDir
from .globals import Globals
from . import buildDir

EXTS_TO_CLEAN = \
[
	".elf",	# Compiled binaries
	".bin",	# Compiled binaries
	".cpp",	# C++ sources generated from .ino
	".d",	# Object files
	".o",	# Object files
]

def __getPathsToClean():
	outputDirPath = buildDir.buildOutputPath()
	if not os.path.isdir(outputDirPath):
		return []

	paths = []

	for root, _, filenames in os.walk(outputDirPath):
		for filename in filenames:
			if os.path.splitext(filename)[1] in EXTS_TO_CLEAN:
				paths.append(os.path.join(root, filename))

	return paths


def cleanTask():
	print("Cleaning files in build directory:", ", ".join(EXTS_TO_CLEAN))
	paths = __getPathsToClean()

	for path in paths:
		os.remove(path)

	print("Clean complete.")
