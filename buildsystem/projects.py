import os
import json

from .globals import Globals

class ProjectConfig():
	def __init__(self):
		self.name = ""
		self.modules = []
		self.warningLevel = "all"
		self.fqbn = ""

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

def __createProjectConfigFromData(configObj : dict):
	config = ProjectConfig()

	# Required:
	config.name = Globals.invokedArgs.project
	config.modules = __getConfigItemMonomorphicContainer(configObj, "modules", list, str)
	config.fqbn = __getConfigItemOfType(configObj, "fqbn", str)

	# Optional:
	warningLevel = __getConfigItemOfType(configObj, "warnings", str, required=False)
	if warningLevel is not None:
		config.warningLevel = warningLevel

	return config

def loadProjectConfig():
	projName = Globals.invokedArgs.project

	if not isValidProject(projName):
		raise ValueError(f"Unrecognised project '{projName}'.")

	configFileName = f"{projName}_config.json"
	pathToConfig = os.path.join(Globals.rootPath, "projects", projName, configFileName)

	if not os.path.isfile(pathToConfig):
		raise OSError(__errorString(f"Config file {configFileName} was not found."))

	configObj = None

	with open(pathToConfig, "r") as inFile:
		configObj = json.load(inFile)

	if type(configObj) is not dict:
		raise ValueError(__errorString(f"Config {configFileName} was not specified as a JSON object."))

	return __createProjectConfigFromData(configObj)

def isValidProject(projName : str):
	return os.path.isdir(os.path.join(Globals.rootPath, "projects", projName))
