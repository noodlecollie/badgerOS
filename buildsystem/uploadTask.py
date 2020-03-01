from . import buildDir
from .globals import Globals
from . import toolchain
from . import buildDir

def __createUploadCallArgs():
	return \
	[
		"upload",
		"-t",
		"--fqbn",
		Globals.projectConfig.fqbn,
		"--port",
		Globals.invokedArgs.port,
		buildDir.projectBuildDirPath()
	]

def uploadTask():
	if Globals.invokedArgs.port is None:
		raise ValueError("An upload port must be specified when running upload task.")

	toolchain.fetchToolchainBinary()
	toolchain.callToolchainExecutable(__createUploadCallArgs())
