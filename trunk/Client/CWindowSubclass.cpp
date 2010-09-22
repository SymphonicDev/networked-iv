//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CWindowSubclass.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

bool    CWindowSubclass::m_bSubclassed = false;
WNDPROC CWindowSubclass::m_wWndProc;

extern CChatWindow * g_pChatWindow;

LRESULT APIENTRY CWindowSubclass::WndProc_Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Does our chat window exist?
	if(g_pChatWindow)
	{
		// Give this input to our chat window
		if(g_pChatWindow->HandleUserInput(uMsg, (DWORD)wParam))
		{
			// The chat window handled it
			return 0;
		}
	}

	return CallWindowProc(m_wWndProc, hWnd, uMsg, wParam, lParam);
}

void CWindowSubclass::Subclass(HWND hWnd)
{
	if(!m_bSubclassed)
	{
		m_wWndProc = SubclassWindow(hWnd, WndProc_Hook);
		m_bSubclassed = true;
	}
}
