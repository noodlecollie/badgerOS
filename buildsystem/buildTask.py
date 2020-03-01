import subprocess

from . import toolchain
from . import buildDir
from .globals import Globals
from .buildOutput import updateFilesInBuildFolder

def __createCompileCallArgs():
	return \
	[
		"compile",
		"--build-path",
		buildDir.buildOutputPath(),
		"--build-cache-path",
		buildDir.buildOutputCachePath(),
		"--fqbn",
		Globals.projectConfig.fqbn,
		"--warnings",
		Globals.projectConfig.warningLevel,
		buildDir.projectBuildDirPath()
	]

def buildTask():
	toolchain.fetchToolchainBinary()
	updateFilesInBuildFolder()
	toolchain.callToolchainExecutable(__createCompileCallArgs())
