#define PROG_HEADER_PREFIX(progName) Prog_##progName
#define PROG_HEADER_PATH(progName) <PROG_HEADER_PREFIX(progName)/progName.h>
#define BOARD_HEADER_PATH(boardName) <PlatformConfig/Platform/boardName.h>
#define BOARD_CONFIG(boardName) (&PlatformConfig::boardName::getConfig)

#ifndef PROG_NAME
#error No PROG_NAME defined!
#endif

#ifndef BOARD_NAME
#error No BOARD_NAME defined!
#endif

#include PROG_HEADER_PATH(PROG_NAME)
#include BOARD_HEADER_PATH(BOARD_NAME)

void setup()
{
	PROG_NAME::setup(BOARD_CONFIG(BOARD_NAME));
}

void loop()
{
	PROG_NAME::loop();
}
