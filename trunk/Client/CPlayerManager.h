//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPlayerManager.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CPlayerManager
{
private:
	CNetworkPlayer * m_pNetworkPlayers[PLAYER_MAX];

public:
	CPlayerManager();
	~CPlayerManager();

	bool             Add(EntityId playerId, String strName);
	bool             Delete(EntityId playerId);
	bool             IsActive(EntityId playerId);
	CNetworkPlayer * Get(EntityId playerId);
	EntityId         GetCount();
};
