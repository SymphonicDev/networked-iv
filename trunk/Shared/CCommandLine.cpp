//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CCommandLine.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

static std::map<String, String> CCommandLine::m_commandLineOptions;

void CCommandLine::Parse()
{
	// Get the command line string
	char * szCommandLine = GetCommandLine();

	while(*szCommandLine)
	{
		// Is the current char not a space?
		if(!isspace(*szCommandLine))
		{
			// Is the current char a '-'?
			if(*szCommandLine == '-')
			{
				// Collect the option string
				String strOption;

				while(*szCommandLine && !isspace(*szCommandLine))
				{
					strOption += *szCommandLine;
					szCommandLine++;
				}

				// If we have run out of command line to process break out of the loop
				if(!(*szCommandLine))
					break;

				// Skip the spaces between the option and the value
				while(*szCommandLine && isspace(*szCommandLine))
					szCommandLine++;

				// If we have run out of command line to process break out of the loop
				if(!(*szCommandLine))
					break;

				// Collect the value string
				String strValue;
				// TODO: Check if the value first char is a '-'?

				while(*szCommandLine && !isspace(*szCommandLine))
				{
					strValue += *szCommandLine;
					szCommandLine++;
				}

				// Add the option and value to the command line options
				
				// Handle the option and value string
				if(!strcmp(strOption.C_String(), "-ip"))
					m_strIp.Set(strValue.C_String());
				else if(!strcmp(strOption.C_String(), "-port"))
					m_usPort = atoi(strValue.C_String());
				else if(!strcmp(strOption.C_String(), "-password"))
					m_strPassword.Set(strValue.C_String());
				else if(!strcmp(strOption.C_String(), "-nick"))
					m_strNick.Set(strValue.C_String());
				else
				{
					CLogFile::Printf("Warning: Unhandled command line parameter %s (%s)", 
						strOption.C_String(), strValue.C_String());
				}

				// If we have run out of command line to process break out of the loop
				if(!(*szCommandLine))
					break;
			}
		}

		// Increment the command line string pointer
		szCommandLine++;
	}
}
