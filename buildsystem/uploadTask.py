from . import buildDir
from .globals import Globals
from . import toolchain
from . import projects

def __validate():
	if Globals.invokedArgs.port is None:
		raise ValueError("An upload port must be specified when running upload task.")

	if not buildDir.buildDirProjectConfigExists():
		raise OSError("No previously built project found - run the 'build' command first.")


def __createUploadCallArgs():
	projectConfig = projects.loadProjectConfig(buildDir.buildDirProjectConfigPath())

	return \
	[
		"upload",
		"-t",
		"--fqbn",
		projectConfig.fqbn,
		"--port",
		Globals.invokedArgs.port,
		buildDir.projectBuildDirPath(projectConfig.name)
	]

def uploadTask():
	__validate()

	toolchain.fetchToolchainBinary()
	toolchain.callToolchainExecutable(__createUploadCallArgs())
