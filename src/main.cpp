// The following allows us to specify the program and board names in the project configuration,
// and cut down on the boilerplate code for starting the program.
#define PROG_HEADER_PREFIX(progName) Prog_##progName
#define PROG_HEADER_PATH(progName) <PROG_HEADER_PREFIX(progName)/progName.h>
#define BOARD_HEADER_PREFIX(boardName) Plat_##boardName
#define BOARD_HEADER_PATH(boardName) <BOARD_HEADER_PREFIX(boardName)/boardName.h>

#ifndef PROG_NAME
#error No PROG_NAME defined!
#endif

#ifndef BOARD_NAME
#error No BOARD_NAME defined!
#endif

#include <PlatformConfig/Platform.h>

#include PROG_HEADER_PATH(PROG_NAME)
#include BOARD_HEADER_PATH(BOARD_NAME)

void setup()
{
	PlatformConfig::ConfigArgs args;
	PROG_NAME::getPlatformConfigArgs(args);

	PlatformConfig::PlatformConfigObject* const configObject = BOARD_NAME::getConfigObject();
	PlatformConfig::initialiseConfig(configObject, args);

	PROG_NAME::setup();
}

void loop()
{
	PROG_NAME::loop();
}
