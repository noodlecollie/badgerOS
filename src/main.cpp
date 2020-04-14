// The following allows us to specify the program and board names in the project configuration,
// and cut down on the boilerplate code for starting the program.
#define PROG_HEADER_PREFIX(progName) Prog_##progName
#define PROG_HEADER_PATH(progName) <PROG_HEADER_PREFIX(progName)/progName.h>
#define BOARD_HEADER_PATH(boardName) <PlatformConfig/Platform/boardName.h>
#define BOARD_CONFIG_FACTORY_FUNC(boardName) (&PlatformConfig::boardName::getConfig)

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
	PlatformConfig::initialiseConfig(BOARD_CONFIG_FACTORY_FUNC(BOARD_NAME));
	PROG_NAME::setup();
}

void loop()
{
	PROG_NAME::loop();
}
