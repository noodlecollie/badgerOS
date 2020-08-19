#include <cstring>
#include <cctype>
#include "CommandArguments.h"

namespace SerialConsole
{
	CommandArguments::CommandArguments(char* command)
	{
		parseCommandString(command);
	}

	// Quoted tokens and escape characters not currently supported.
	void CommandArguments::parseCommandString(char* command)
	{
		memset(m_Argv, 0, sizeof(m_Argv));
		m_Argc = 0;

		if ( !command || !(*command) )
		{
			return;
		}

		bool lastCharWasDelimiter = true;

		for ( ; (*command) && m_Argc < MAX_ARGS; ++command )
		{
			if ( isspace(*command) )
			{
				// Delimit tokens with nulls.
				*command = '\0';
				lastCharWasDelimiter = true;
				continue;
			}

			if ( lastCharWasDelimiter )
			{
				m_Argv[m_Argc++] = command;
				lastCharWasDelimiter = false;
				continue;
			}
		}
	}
}
