//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CServer.h
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CServer
{
private:
	bool  m_bActive;
	DWORD m_dwLastFPSUpdateTickCount;
	DWORD m_dwFrameCount;
	DWORD m_dwFramesPerSecond;

public:
	CServer();
	~CServer();

	void        OnLoad();
	void        Process();
	void        OnUnload();
	bool        IsActive();
	void        SetTitle(String strTitle);
};
