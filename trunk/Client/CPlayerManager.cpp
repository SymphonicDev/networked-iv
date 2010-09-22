//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPlayerManager.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CPlayerManager::CPlayerManager()
{
	// Loop through all network player pointers
	for(EntityId i = 0; i < PLAYER_MAX; i++)
	{
		// Set this network player pointer to NULL
		m_pNetworkPlayers[i] = NULL;
	}
}

CPlayerManager::~CPlayerManager()
{
	// Loop through all network player pointers
	for(EntityId i = 0; i < PLAYER_MAX; i++)
	{
		// Is this network player pointer valid?
		if(m_pNetworkPlayers[i])
		{
			// Delete this network player
			SAFE_DELETE(m_pNetworkPlayers[i]);
		}
	}
}

bool CPlayerManager::Add(EntityId playerId, String strName)
{
	// Is this player already added?
	if(IsActive(playerId))
		return false;

	// Create the network player instance
	m_pNetworkPlayers[playerId] = new CNetworkPlayer(playerId, strName);

	// Was the network player instance created?
	if(m_pNetworkPlayers[playerId])
	{
		return true;
	}

	return false;
}

bool CPlayerManager::Delete(EntityId playerId)
{
	// Is this player not active?
	if(!IsActive(playerId))
		return false;

	// Delete the network player instance
	delete m_pNetworkPlayers[playerId];

	// Set the player pointer to NULL
	m_pNetworkPlayers[playerId] = NULL;

	return true;
}

bool CPlayerManager::IsActive(EntityId playerId)
{
	// Is the player id invalid?
	if(playerId >= PLAYER_MAX)
		return false;

	return (m_pNetworkPlayers[playerId] != NULL);
}

CNetworkPlayer * CPlayerManager::Get(EntityId playerId)
{
	// Is this player not active?
	if(!IsActive(playerId))
		return NULL;

	return m_pNetworkPlayers[playerId];
}

EntityId CPlayerManager::GetCount()
{
	EntityId count = 0;

	// Loop through all players
	for(EntityId i = 0; i < PLAYER_MAX; i++)
	{
		// Is the current player active?
		if(IsActive(i))
		{
			// Increment the player count
			count++;
		}
	}

	return count;
}

void CPlayerManager::SetLocalId(EntityId localId)
{
	m_localId = localId;
}

EntityId CPlayerManager::GetLocalId()
{
	return m_localId;
}
