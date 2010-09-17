//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CConfig.h
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CConfig
{
private:
	CXML * m_pXML;

public:
	CConfig();
	~CConfig();

	bool Open(String strFileName);
	bool GetValueAsString(String strKey, String * strValue);
	bool GetValueAsInteger(String strKey, int * iValue);
	bool GetValueFloat(String strKey, float * fValue);
	bool GetValueAsBoolean(String strKey, bool * bValue);
};
