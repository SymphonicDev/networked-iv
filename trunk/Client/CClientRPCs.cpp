//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CClientRPCs.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CChatWindow *    g_pChatWindow;
extern CPlayerManager * g_pPlayerManager;

void CClientRPCs::InitialData(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Got InitialData RPC from server");

	// Read the data the server sent us
	EntityId ourPlayerId;

	// Read our player id
	if(!pBitStream->ReadCompressed(ourPlayerId))
		return;

	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Connected to the server with player id %d", ourPlayerId);
}

void CClientRPCs::AddPlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Got AddPlayer RPC from server");

	// Read the data the server sent us
	EntityId newPlayerId;
	String strName;

	// Read the new player id
	if(!pBitStream->ReadCompressed(newPlayerId))
		return;

	// Read the player name
	if(!pBitStream->Read(strName))
		return;

	// Add this player to the player manager
	g_pPlayerManager->Add(newPlayerId, strName);

	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "%s (Id: %d) has connected to the server", strName.C_String(), newPlayerId);
}

void CClientRPCs::DeletePlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Got DeletePlayer RPC from server");

	// Read the data the server sent us
	EntityId newPlayerId;

	// Read the new player id
	if(!pBitStream->ReadCompressed(newPlayerId))
		return;

	// Get the network player pointer
	CNetworkPlayer * pNetworkPlayer = g_pPlayerManager->Get(newPlayerId);

	// Is the network player pointer valid?
	if(pNetworkPlayer)
	{
		g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "%s (Id: %d) has disconnected from the server", pNetworkPlayer->GetName().C_String(), newPlayerId);

		// Delete this player from the player manager
		g_pPlayerManager->Delete(playerId);
	}
	else
	{
		g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Invalid player (Id: %d) has disconnected to the server", newPlayerId);
	}
}

void CClientRPCs::SpawnPlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Got SpawnPlayer RPC from server");
}

void CClientRPCs::DestroyPlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Got DestroyPlayer RPC from server");
}

void CClientRPCs::Register(CRPCHandler * pRPCHandler)
{
	pRPCHandler->AddFunction(RPC_INITIAL_DATA, InitialData);
	pRPCHandler->AddFunction(RPC_ADD_PLAYER, AddPlayer);
	pRPCHandler->AddFunction(RPC_DELETE_PLAYER, DeletePlayer);
	pRPCHandler->AddFunction(RPC_SPAWN_PLAYER, SpawnPlayer);
	pRPCHandler->AddFunction(RPC_DESTROY_PLAYER, DestroyPlayer);
}

void CClientRPCs::Unregister(CRPCHandler * pRPCHandler)
{
	pRPCHandler->RemoveFunction(RPC_INITIAL_DATA);
	pRPCHandler->RemoveFunction(RPC_ADD_PLAYER);
	pRPCHandler->RemoveFunction(RPC_DELETE_PLAYER);
	pRPCHandler->RemoveFunction(RPC_SPAWN_PLAYER);
	pRPCHandler->RemoveFunction(RPC_DESTROY_PLAYER);
}
