//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CClient.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CClient
{
private:
	unsigned int m_uiBaseAddress;
	String m_strIp;
	unsigned short m_usPort;
	String m_strPassword;
	String m_strNick;

public:
	bool         OnLoad();
	void         OnUnload();
	unsigned int GetBaseAddress();
	void         OnD3DCreateDevice(IDirect3DDevice9 * pD3DDevice);
	void         OnD3DLostDevice(IDirect3DDevice9 * pD3DDevice);
	void         OnD3DResetDevice(IDirect3DDevice9 * pD3DDevice);
	void         OnD3DBeginScene(IDirect3DDevice9 * pD3DDevice);
	void         OnD3DEndScene(IDirect3DDevice9 * pD3DDevice);
	void         OnGameLoad();
	String       GetNick();
};
