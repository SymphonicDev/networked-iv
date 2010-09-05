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

#define FUNC_DeletePlayer 0x81B960

class CPlayer
{
private:
	static bool m_bPlayerPedSlotState[PLAYER_MAX];
	unsigned int m_uiPlayerIndex;
	CIVPlayerPed * m_pPlayerPed;
	DWORD m_dwModelHash;

public:
	CPlayer(bool bLocalPlayer);
	~CPlayer();

	bool  IsLocalPlayer();
	bool  IsSpawned();
	bool  Create();
	void  Destroy();
	bool  SetModelByHash(DWORD dwModelHash);
	DWORD GetModelHash();
	bool  SetPosition(Vector3 * vecPosition);
	bool  GetPosition(Vector3 * vecPosition);
};
