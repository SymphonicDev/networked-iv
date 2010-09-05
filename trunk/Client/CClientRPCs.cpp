//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CClientRPCs.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CChatWindow * g_pChatWindow;

void CClientRPCs::InitialData(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Got InitialData RPC from server");

	// Read the data the server sent us
	EntityId ourPlayerId;

	// Read our player id
	if(!pBitStream->ReadCompressed(ourPlayerId))
		return;

	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Joined the game with player id %d", ourPlayerId);
}

void CClientRPCs::AddPlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Got AddPlayer RPC from server");
}

void CClientRPCs::DeletePlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Got DeletePlayer RPC from server");
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
