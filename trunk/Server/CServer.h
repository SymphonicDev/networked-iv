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
	bool               m_bActive;
	bool               m_bShowFPS;
	DWORD              m_dwLastFPSUpdateTickCount;
	DWORD              m_dwFrameCount;
	DWORD              m_dwFramesPerSecond;
	CMutex             m_inputQueueMutex; // Mutex for m_inputQueue
	std::queue<String> m_inputQueue;

	void        ProcessInputQueue();

public:
	CServer();
	~CServer();

	bool        OnLoad();
	void        Process();
	void        OnUnload();
	bool        IsActive();
	void        SetTitle(String strTitle);
	void        OnCloseEvent();
	void        AddToInputQueue(String strString);
	String      GetConfigString(String strKey, String strDefaultValue);
	int         GetConfigInteger(String strKey, int iDefaultValue);
	float       GetConfigFloat(String strKey, float fDefaultValue);
	bool        GetConfigBoolean(String strKey, bool bDefaultValue);
};
