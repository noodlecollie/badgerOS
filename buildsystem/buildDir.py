import os
import shutil

from .globals import Globals

def buildDirPath():
	return os.path.join(Globals.rootPath, "build")

def buildDirProjectConfigPath():
	return os.path.join(buildDirPath(), "projectConfig.json")

def projectBuildDirPath(project : str):
	return os.path.join(buildDirPath(), project)

def buildOutputPath() :
	return os.path.join(buildDirPath(), "_output")

def buildOutputCachePath():
	return os.path.join(buildOutputPath(), "cache")

def ensureBuildDirExists():
	path = buildDirPath()

	if os.path.isdir(path):
		return

	if os.path.isfile(path):
		os.remove(path)

	os.makedirs(path)

def recreateBuildDir():
	path = buildDirPath()
	shutil.rmtree(path, ignore_errors=True)
	ensureBuildDirExists()

def recreateProjectBuildDir(project : str):
	recreateBuildDir()
	os.makedirs(projectBuildDirPath(project))

def buildDirProjectConfigExists():
	return os.path.isfile(buildDirProjectConfigPath())
