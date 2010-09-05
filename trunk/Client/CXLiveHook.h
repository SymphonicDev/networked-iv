//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CXLiveHook.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================
// Parts are public domain code from xliveless by listener

#pragma once

#include <StdInc.h>

class CXLiveHook
{
private:
	bool m_bInstalled;

public:
	CXLiveHook();

	void Install();
	void Uninstall();
};
