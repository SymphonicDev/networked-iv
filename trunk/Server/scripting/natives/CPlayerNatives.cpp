//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPlayerNatives.cpp
// Project: Server
// Author(s): mabako
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

void CPlayerNatives::LoadFunctions(CSquirrel* pSquirrel)
{
	pSquirrel->RegisterFunction("getPlayerName", GetName, 1, "p");
	pSquirrel->RegisterFunction("getPlayerIP", GetIP, 1, "p");
}

int CPlayerNatives::GetName(SQVM* pVM)
{
	CPlayer* player = sq_toplayer(pVM, 2);
	if(player)
		sq_pushstring(pVM, player->GetName(), strlen(player->GetName()));
	else
		sq_pushnull(pVM);
	return 1;
}

int CPlayerNatives::GetIP(SQVM* pVM)
{
	CPlayer* player = sq_toplayer(pVM, 2);
	if(player)
		sq_pushstring(pVM, player->GetIP(), strlen(player->GetIP()));
	else
		sq_pushnull(pVM);
	return 1;
}
