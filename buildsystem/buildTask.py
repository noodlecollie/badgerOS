import subprocess

from . import toolchain
from . import buildDir
from . import projects
from . import buildDir
from .globals import Globals
from .buildOutput import updateFilesInBuildFolder

def __getCustomDefines():
	if Globals.debugBuild:
		return "-DDEBUG"
	else:
		return ""

def __createCompileCallArgs():
	projectConfig = projects.loadProjectConfig(buildDir.buildDirProjectConfigPath())

	return \
	[
		"compile",
		"--build-path",
		buildDir.buildOutputPath(),
		"--build-cache-path",
		buildDir.buildOutputCachePath(),
		"--fqbn",
		projectConfig.fqbn,
		"--warnings",
		projectConfig.warningLevel,
		"--build-properties",
		"build.defines=" + __getCustomDefines(),
		buildDir.projectBuildDirPath(projectConfig.name)
	]

def buildTask():
	if Globals.invokedArgs.project is None:
		raise ValueError("No --project specified for building.")

	toolchain.fetchToolchainBinary()
	updateFilesInBuildFolder()
	toolchain.callToolchainExecutable(__createCompileCallArgs())
