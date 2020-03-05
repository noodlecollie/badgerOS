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
	".o",	# Object files,
	".ino"	# Auto-generated Arduino sources
]

def __getPathsToClean():
	buildPath = buildDir.buildDirPath()
	if not os.path.isdir(buildPath):
		return []

	paths = []

	for root, _, filenames in os.walk(buildPath):
		for filename in filenames:
			if os.path.splitext(filename)[1] in EXTS_TO_CLEAN:
				paths.append(os.path.join(root, filename))

	return paths


def cleanTask():
	print("Cleaning files in build directory:", ", ".join(EXTS_TO_CLEAN))

	paths = __getPathsToClean()
	print("Cleaning", len(paths), "files.")

	for path in paths:
		os.remove(path)

	print("Clean complete.")
