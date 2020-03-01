import argparse
import os
import sys

from buildsystem.globals import Globals
from buildsystem import projects
from buildsystem import buildDir
from buildsystem.cleanTask import cleanTask
from buildsystem.buildTask import buildTask
from buildsystem.uploadTask import uploadTask

TASK_CALLBACKS = \
{
	"clean": cleanTask,
	"build": buildTask,
	"upload": uploadTask
}

def scriptDirPath():
	return os.path.dirname(os.path.realpath(__file__))

def parseArguments():
	parser = argparse.ArgumentParser("build.py", description="Builds the specified project")

	parser.add_argument("-p", "--project",
						required=True,
						help="Project to perform tasks for.")

	parser.add_argument("--port",
						help="Port to use for uploading compiled binaries.")

	parser.add_argument("--stack",
						action="store_true",
						help="If true, fatal exceptions will be logged so that the stack trace is visible.")

	parser.add_argument("tasks",
						nargs="*",
						choices=TASK_CALLBACKS.keys(),
						help="Tasks to perform.")

	return parser.parse_args()

def validateArgs(args):
	if not projects.isValidProject(args.project):
		raise ValueError(f"Project '{args.project}' does not exist.")

def main():
	Globals.rootPath = scriptDirPath()

	Globals.invokedArgs = parseArguments()
	validateArgs(Globals.invokedArgs)

	Globals.projectConfig = projects.loadProjectConfig()
	buildDir.ensureBuildDirExists()

	for task in Globals.invokedArgs.tasks:
		print("*** Running task:", task)

		try:
			TASK_CALLBACKS[task]()
		except Exception as ex:
			if not Globals.invokedArgs.stack:
				print("An error occurred.", str(ex), file=sys.stderr)
				sys.exit(1)
			else:
				raise ex

if __name__ == "__main__":
	main()
