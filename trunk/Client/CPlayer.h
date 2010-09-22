//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPlayer.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

//#define FUNC_CreatePlayerPed_6 0x81CDD0
#define FUNC_CreatePlayerPed_7 0x81CB90
//#define FUNC_SetupPedIntelligence_6 0x89EE30
#define FUNC_SetupPedIntelligence_7 0x89EC20
#define FUNC_CPlayerPed__Destructor_7 0x9C2260 // TODO: Use VFTable
#define FUNC_DeletePlayer 0x81B960

class CPlayer
{
private:
	unsigned int   m_uiPlayerIndex;
	CIVPlayerPed * m_pPlayerPed;
	DWORD          m_dwModelHash;
	unsigned int   m_uiScriptingHandle;

public:
	CPlayer(bool bLocalPlayer);
	~CPlayer();

	bool  IsLocalPlayer();
	bool  IsSpawned();
	bool  Create();
	void  Destroy();
	bool  SetModelByHash(DWORD dwModelHash);
	DWORD GetModelHash();
	bool  SetPosition(Vector3 * vecPosition, bool bRemoveFromWorld = true);
	bool  GetPosition(Vector3 * vecPosition);
};
