//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPlayer.cpp
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CNetworkManager * g_pNetworkManager;
extern CPlayerManager *  g_pPlayerManager;

CPlayer::CPlayer(EntityId playerId, String strName)
{
	m_playerId = playerId;
	m_strName.SetLimit(NICK_MAX);
	m_strName.Set(strName.C_String());
	m_bSpawned = false;
}

CPlayer::~CPlayer()
{

}

EntityId CPlayer::GetPlayerId()
{
	return m_playerId;
}

String CPlayer::GetName()
{
	return m_strName;
}

bool CPlayer::IsSpawned()
{
	return m_bSpawned;
}

void CPlayer::AddForPlayer(EntityId playerId)
{
	// Construct the BitStream
	CBitStream bitStream;
	bitStream.WriteCompressed(m_playerId);
	bitStream.Write(m_strName);

	// Send it to the player
	g_pNetworkManager->RPC(RPC_ADD_PLAYER, &bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, playerId, false);
}

void CPlayer::AddForWorld()
{
	// Loop through all players
	for(EntityId i = 0; i < PLAYER_MAX; i++)
	{
		// Is the current player not this player and active?
		if(i != m_playerId && g_pPlayerManager->IsActive(i))
		{
			// Add this player for the current player
			AddForPlayer(i);
		}
	}
}

void CPlayer::DeleteForPlayer(EntityId playerId)
{
	// Construct the BitStream
	CBitStream bitStream;
	bitStream.Write(m_playerId);

	// Send it to the player
	g_pNetworkManager->RPC(RPC_DELETE_PLAYER, &bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, playerId, false);

}
void CPlayer::DeleteForWorld()
{
	// Loop through all players
	for(EntityId i = 0; i < PLAYER_MAX; i++)
	{
		// Is the current player not this player and active?
		if(i != m_playerId && g_pPlayerManager->IsActive(i))
		{
			// Delete this player for the current player
			DeleteForPlayer(i);
		}
	}
}

void CPlayer::SpawnForPlayer(EntityId playerId)
{
	// Construct the BitStream
	CBitStream bitStream;
	bitStream.Write(m_playerId);

	// Send it to the player
	g_pNetworkManager->RPC(RPC_SPAWN_PLAYER, &bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, playerId, false);
}

void CPlayer::SpawnForWorld()
{
	// Loop through all players
	for(EntityId i = 0; i < PLAYER_MAX; i++)
	{
		// Is the current player not this player and active?
		if(i != m_playerId && g_pPlayerManager->IsActive(i))
		{
			// Spawn this player for the current player
			SpawnForPlayer(i);
		}
	}

	// Mark us as spawned
	m_bSpawned = true;
}

void CPlayer::DestroyForPlayer(EntityId playerId)
{
	// Construct the BitStream
	CBitStream bitStream;
	bitStream.Write(m_playerId);

	// Send it to the player
	g_pNetworkManager->RPC(RPC_DESTROY_PLAYER, &bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, playerId, false);
}

void CPlayer::DestroyForWorld()
{
	// Loop through all players
	for(EntityId i = 0; i < PLAYER_MAX; i++)
	{
		// Is the current player not this player and active?
		if(i != m_playerId && g_pPlayerManager->IsActive(i))
		{
			// Destroy this player for the current player
			DestroyForPlayer(i);
		}
	}

	// Mark us as not spawned
	m_bSpawned = false;
}
