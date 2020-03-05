import sys
import os
import glob
import shutil
import json

from . import buildDir
from . import projects
from .globals import Globals

SOURCE_FILE_EXTENSIONS = [".h", ".cpp", ".ino"]

class SearchPath():
	def __init__(self):
		# When files are copied into the build directory, their relative path will be computed with respect to srcRoot.
		# The files will then be copied to the build dir according to this path, but relative to destRoot.
		self.srcRoot = ""
		self.destRoot = ""

class FileCopyMapping():
	def __init__(self, src : str = "", dest : str = ""):
		self.src = src
		self.dest = dest

	def __repr__(self):
		return f"(src={self.src}, dest={self.dest})"

def __createSearchPaths(projectConfig):
	buildRootPath = buildDir.buildDirPath()

	projectRootSrcPath = os.path.join(Globals.rootPath, "projects", projectConfig.name)
	projectRootDestPath = os.path.join(buildRootPath, projectConfig.name)

	modulesRootSrcPath = os.path.join(Globals.rootPath, "modules")
	modulesRootDestPath = os.path.join(projectRootDestPath, "src")

	searchPaths = []

	projectSearchPath = SearchPath()
	projectSearchPath.srcRoot = projectRootSrcPath
	projectSearchPath.destRoot = projectRootDestPath
	searchPaths.append(projectSearchPath)

	for module in projectConfig.modules:
		searchPath = SearchPath()

		searchPath.srcRoot = os.path.join(modulesRootSrcPath, module)
		searchPath.destRoot = os.path.join(modulesRootDestPath, module)

		searchPaths.append(searchPath)

	return searchPaths

def __findSourcesRecursively(searchPaths : list):
	foundFiles = []

	for path in searchPaths:
		for root, _, filenames in os.walk(path.srcRoot):
			for filename in filenames:
				if os.path.splitext(filename)[1] in SOURCE_FILE_EXTENSIONS:
					srcPath = os.path.join(root, filename)
					destPath = os.path.join(path.destRoot, os.path.relpath(srcPath, path.srcRoot))
					foundFiles.append(FileCopyMapping(srcPath, destPath))

	return foundFiles

def __srcIsNewer(src, dest):
	return (not os.path.exists(dest)) or (os.stat(src).st_mtime - os.stat(dest).st_mtime > 1)

def __calcFilesNeedingCopy(foundFiles : list):
	return [item for item in foundFiles if __srcIsNewer(item.src, item.dest)]

def __copyFile(src, dest):
	destDir = os.path.dirname(dest)
	if not os.path.isdir(destDir):
		os.makedirs(destDir)

	shutil.copy2(src, dest)

def __copyFiles(destRoot : str, files : list):
	if len(files) < 1:
		print("All files in", destRoot, "are up to date.")
		return

	print("Updating", len(files), "files in", destRoot)

	for i in range(0, len(files)):
		item = files[i]
		print(f"[{i}] {item.src} -> {item.dest}")

		__copyFile(item.src, item.dest)

def __createIno(path : str):
	projectNamespace = f"Project_{Globals.invokedArgs.project}"

	with open(path, "w") as outFile:
		outFile.write("// We use the C-style \"extern\" method here, to allow these functions to be defined\n")
		outFile.write("// anywhere so that we don't have to depend on a specific header file.\n")
		outFile.write("\n")
		outFile.write(f"namespace {projectNamespace}\n")
		outFile.write("{\n")
		outFile.write(f"\textern void setup();\n")
		outFile.write(f"\textern void loop();\n")
		outFile.write("}\n")
		outFile.write("\n")
		outFile.write("void setup()\n")
		outFile.write("{\n")
		outFile.write(f"\t{projectNamespace}::setup();\n")
		outFile.write("}\n")
		outFile.write("\n")
		outFile.write("void loop()\n")
		outFile.write("{\n")
		outFile.write(f"\t{projectNamespace}::loop();\n")
		outFile.write("}\n")

	print("Auto-generated .ino:", path)

def __writeProjectConfigToBuildDir(projectConfig):
	outPath = buildDir.buildDirProjectConfigPath()
	print("Caching project config as:", outPath)

	with open(outPath, "w") as outFile:
		json.dump(projectConfig.toDict(), outFile)

def updateFilesInBuildFolder():
	projectConfig = projects.loadProjectConfig()
	buildPath = buildDir.buildDirPath()
	projectBuildRootDir = buildDir.projectBuildDirPath(projectConfig.name)

	if not os.path.isdir(projectBuildRootDir):
		# We were not previously configured for this project, so wipe and recreate.
		buildDir.recreateProjectBuildDir(projectConfig.name)

	__writeProjectConfigToBuildDir(projectConfig)

	projectInoPath = os.path.join(projectBuildRootDir, f"{Globals.invokedArgs.project}.ino")
	if not os.path.isfile(projectInoPath):
		__createIno(projectInoPath)

	searchPaths = __createSearchPaths(projectConfig)
	foundFiles = __findSourcesRecursively(searchPaths)
	filesRequiredToCopy = __calcFilesNeedingCopy(foundFiles)
	__copyFiles(buildPath, filesRequiredToCopy)
