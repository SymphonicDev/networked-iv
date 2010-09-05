//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVWorld.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CClient * g_pClient;

void CIVWorld::Add(IVEntity * pEntity, BOOL bUnknown)
{
	DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CWorld__Add_7);
	_asm
	{
		push bUnknown
		push pEntity
		call dwFunc
		add esp, 8
	}
}

void CIVWorld::Remove(IVEntity * pEntity, BOOL bUnknown)
{
	DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CWorld__Remove_7);
	_asm
	{
		push bUnknown
		push pEntity
		call dwFunc
		add esp, 8
	}
}
