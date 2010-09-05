//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CLogFile.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CLogFile
{
private:
	static FILE * m_fLogFile;

public:
	static void Open(char * szLogFile);
	static void Printf(const char * szFormat, ...);
	static void Close();
};
