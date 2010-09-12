//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CLogFile.cpp
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

// TODO: A custom function that gets called after CLogFile::Printf (CLogFile::SetCustomCallback)
// (Useful for outputting log messages to the chatbox, adding a scripting function, e.t.c.)
#include <StdInc.h>

FILE * CLogFile::m_fLogFile;

void CLogFile::Open(char * szLogFile, bool bAppend)
{
	// Get the log file path
	char szPath[MAX_PATH];
	sprintf(szPath, "%s%s", SharedUtility::GetAppPath(), szLogFile);

	// Open the log file
	m_fLogFile = fopen(szPath, bAppend ? "a" : "w");

	// Did the log file open successfully?
	if(m_fLogFile)
	{
		// Log the log file started message
		Printf("Log file started");
	}
}

void CLogFile::Printf(const char * szFormat, ...)
{
	// Collect the arguments
	va_list vaArgs;
	char szBuffer[512];
	va_start(vaArgs, szFormat);
	vsprintf(szBuffer, szFormat, vaArgs);
	va_end(vaArgs);

	// Print the message
	printf("%s\n", szBuffer);

	// Is the log file open?
	if(m_fLogFile)
	{
		// Log the message
		fprintf(m_fLogFile, "[%s] %s\n", SharedUtility::GetTime(), szBuffer);

		// Flush the log file
		fflush(m_fLogFile);
	}
}

void CLogFile::Close()
{
	// Is the log file open?
	if(m_fLogFile)
	{
		// Log the log file finished message
		Printf("Log file finished");

		// Close the log file
		fclose(m_fLogFile);
		m_fLogFile = NULL;
	}
}
