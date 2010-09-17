//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetworkPlayer.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CNetworkPlayer::CNetworkPlayer(EntityId playerId, String strName)
{
	// Set our player id
	m_playerId = playerId;

	// Set our name
	m_strName = strName;

	// Create our player instance
	m_pPlayer = new CPlayer(false);
}

CNetworkPlayer::~CNetworkPlayer()
{
	// Delete our player instance
	SAFE_DELETE(m_pPlayer);
}

EntityId CNetworkPlayer::GetId()
{
	return m_playerId;
}

void CNetworkPlayer::SetId(EntityId id)
{
	// Set our id
	m_playerId = id;
}

String CNetworkPlayer::GetName()
{
	return m_strName;
}

void CNetworkPlayer::SetName(String strName)
{
	// Set our name
	m_strName = strName;
}

CPlayer * CNetworkPlayer::GetPlayer()
{
	return m_pPlayer;
}
