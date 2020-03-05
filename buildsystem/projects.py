import os
import json

from .globals import Globals

class ProjectConfig():
	def __init__(self):
		self.name = ""
		self.modules = []
		self.warningLevel = "all"
		self.fqbn = ""

	def toDict(self):
		return \
		{
			"name": self.name,
			"modules": self.modules,
			"warnings": self.warningLevel,
			"fqbn": self.fqbn
		}

def __errorString(error : str):
	return f"Project '{Globals.invokedArgs.project}': {error}"

def __getConfigItem(configObj : dict, key : str, required : bool = True):
	if required and key not in configObj:
		raise KeyError(__errorString(f"Required item '{key}' was not present in project config."))

	return configObj[key] if key in configObj else None

def __getConfigItemOfType(configObj : dict, key : str, desiredType, required : bool = True):
	data = __getConfigItem(configObj, key, required)

	if type(data) is not desiredType and (required or type(data) is not type(None)):
		raise TypeError(__errorString(f"Config item '{key}' was not of type '{desiredType.__name__}'."))

	return data

def __getConfigItemMonomorphicContainer(configObj : dict, key : str, desiredType, desiredItemType, required : bool = True):
	data = __getConfigItemOfType(configObj, key, desiredType, required)

	for i in range(0, len(data)):
		item = data[i]

		if type(item) is not desiredItemType:
			raise TypeError(__errorString(f"Config item '{key}' sub-item at index {i} was not of type '{desiredItemType.__name__}'."))

	return data

def __createProjectConfigFromData(configObj : dict, projectName):
	config = ProjectConfig()

	# Required:
	config.name = projectName if projectName is not None else __getConfigItemOfType(configObj, "name", str)
	config.modules = __getConfigItemMonomorphicContainer(configObj, "modules", list, str)
	config.fqbn = __getConfigItemOfType(configObj, "fqbn", str)

	# Optional:
	warningLevel = __getConfigItemOfType(configObj, "warnings", str, required=False)
	if warningLevel is not None:
		config.warningLevel = warningLevel

	return config

# TODO: Make this process nicer.
def loadProjectConfig(overridePath=None):
	pathToConfig = ""
	projectName = None

	if overridePath is None:
		projectName = Globals.invokedArgs.project

		if projectName is None:
			raise ValueError("No project specified - use the --project switch.")

		if not isValidProject(projectName):
			raise ValueError(f"Unrecognised project '{projectName}'.")

		configFileName = f"{projectName}_config.json"
		pathToConfig = os.path.join(Globals.rootPath, "projects", projectName, configFileName)
	else:
		pathToConfig = overridePath

	if not os.path.isfile(pathToConfig):
		raise OSError(__errorString(f"Config file {pathToConfig} was not found."))

	configObj = None

	with open(pathToConfig, "r") as inFile:
		configObj = json.load(inFile)

	if type(configObj) is not dict:
		raise ValueError(__errorString(f"Config {pathToConfig} was not specified as a JSON object."))

	return __createProjectConfigFromData(configObj, projectName)

def isValidProject(projName : str):
	return os.path.isdir(os.path.join(Globals.rootPath, "projects", projName))
