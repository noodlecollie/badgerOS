import platform
import sys
import os
import urllib.request
import subprocess

from zipfile import ZipFile
from .globals import Globals

# TODO: Find a way to download the latest releases rather than staying fixed to one version.
CLI_EXE_URLS = \
{
	"win32":
	{
		"32": "https://github.com/arduino/arduino-cli/releases/download/0.9.0/arduino-cli_0.9.0_Windows_32bit.zip",
		"64": "https://github.com/arduino/arduino-cli/releases/download/0.9.0/arduino-cli_0.9.0_Windows_64bit.zip"
	}
}

CLI_EXE_FILENAME = \
{
	"win32": "arduino-cli.exe"
}

def __is64bit():
	# This is probably not exhaustive, but not sure there's a better way.
	return platform.machine().endswith("64")

def __getCliUrl():
	if sys.platform not in CLI_EXE_URLS:
		raise OSError(f"The current platform {sys.platform} does not have toolchain support implemented.")

	platformMap = CLI_EXE_URLS[sys.platform]
	key = "64" if __is64bit() else "32"

	if key not in platformMap:
		raise OSError(f"No {key}-bit toolchain available for platform {sys.platform}.")

	return platformMap[key]

def __getExeFileName():
	if sys.platform not in CLI_EXE_FILENAME:
		raise OSError(f"The current platform {sys.platform} does not have toolchain support implemented.")

	return CLI_EXE_FILENAME[sys.platform]

def __downloadToolchainZip():
	url = __getCliUrl()
	binDir = toolchainBinDir()
	downloadFilePath = toolchainZipPath()

	if os.path.isfile(downloadFilePath):
		os.remove(downloadFilePath)

	if os.path.isfile(binDir):
		os.remove(binDir)

	if not os.path.isdir(binDir):
		os.makedirs(binDir)

	print("Downloading toolchain:", url)
	with urllib.request.urlopen(url) as remoteFile:
		with open(downloadFilePath, "wb") as localFile:
			localFile.write(remoteFile.read())

	if not os.path.isfile(downloadFilePath):
		raise OSError(f"Could not download toolchain zip {url}")

def __extractToolchainZip():
	zipPath = toolchainZipPath()

	print("Extracting toolchain...")
	with ZipFile(zipPath, "r") as toolchainZip:
		toolchainZip.extractall(path=toolchainBinDir())

	binPath = toolchainBinExecutablePath()
	if not os.path.isfile(binPath):
		raise OSError(f"Could not find {binPath} after extraction of toolchain zip.")

def fetchToolchainBinary():
	if not os.path.isfile(toolchainBinExecutablePath()):
		__downloadToolchainZip()
		__extractToolchainZip()
		print("Toolchain updated.")

def toolchainBinDir():
	return os.path.join(Globals.rootPath, "buildsystem", "bin")

def toolchainZipPath():
	return os.path.join(toolchainBinDir(), "toolchain.zip")

def toolchainBinExecutablePath():
	return os.path.join(toolchainBinDir(), __getExeFileName())

def callToolchainExecutable(args : list):
	processArgs = [toolchainBinExecutablePath()] + args

	print("Calling:", " ".join(processArgs))
	retVal = subprocess.run(processArgs)

	if retVal.returncode != 0:
		raise OSError(f"Call to toolchain executable returned error code {retVal.returncode}.")
	else:
		print("Call completed successfully.")
