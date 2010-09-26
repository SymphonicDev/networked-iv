//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPlayer.h
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CPlayer : public CEntity
{
private:
	EntityId m_playerId;
	String m_strName;
	bool m_bSpawned;

public:
	CPlayer(EntityId playerId, String strName);
	~CPlayer();

	EntityId GetPlayerId();
	String   GetName();
	String   GetIP();
	bool     IsSpawned();
	void     AddForPlayer(EntityId playerId);
	void     AddForWorld();
	void     DeleteForPlayer(EntityId playerId);
	void     DeleteForWorld();
	void     SpawnForPlayer(EntityId playerId);
	void     SpawnForWorld();
	void     DestroyForPlayer(EntityId playerId);
	void     DestroyForWorld();
};
