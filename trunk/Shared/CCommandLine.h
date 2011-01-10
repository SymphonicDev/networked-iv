//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CCommandLine.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CCommandLine
{
private:
	static std::map<String, String> m_commandLineOptions;

public:
	void Parse();
};
