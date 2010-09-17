//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetworkPlayer.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CNetworkPlayer
{
private:
	EntityId m_playerId;
	String m_strName;
	CPlayer * m_pPlayer;

public:
	CNetworkPlayer(EntityId playerId, String strName);
	~CNetworkPlayer();

	EntityId  GetId();
	void      SetId(EntityId id);
	String    GetName();
	void      SetName(String strName);
	CPlayer * GetPlayer();
};
