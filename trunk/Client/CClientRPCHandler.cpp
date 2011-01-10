//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CClientRPCHandler.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CClient * g_pClient;

void CClientRPCHandler::InitialData(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "Got InitialData RPC from server");

	// Read the data the server sent us
	EntityId ourPlayerId;

	// Read our player id
	if(!pBitStream->ReadCompressed(ourPlayerId))
		return;

	// Set local player id
	g_pClient->GetPlayerManager()->SetLocalId(ourPlayerId);

	g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "Connected to the server with player id %d", ourPlayerId);
}

void CClientRPCHandler::AddPlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "Got AddPlayer RPC from server");

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
	g_pClient->GetPlayerManager()->Add(newPlayerId, strName);

	g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "%s (Id: %d) has connected to the server", strName.C_String(), newPlayerId);
}

void CClientRPCHandler::DeletePlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "Got DeletePlayer RPC from server");

	// Read the data the server sent us
	EntityId newPlayerId;

	// Read the new player id
	if(!pBitStream->ReadCompressed(newPlayerId))
		return;

	// Get the network player pointer
	CNetworkPlayer * pNetworkPlayer = g_pClient->GetPlayerManager()->Get(newPlayerId);

	// Is the network player pointer valid?
	if(pNetworkPlayer)
	{
		g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "%s (Id: %d) has disconnected from the server", pNetworkPlayer->GetName().C_String(), newPlayerId);

		// Delete this player from the player manager
		g_pClient->GetPlayerManager()->Delete(playerId);
	}
	else
	{
		g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "Invalid player (Id: %d) has disconnected to the server", newPlayerId);
	}
}

void CClientRPCHandler::SpawnPlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "Got SpawnPlayer RPC from server");
}

void CClientRPCHandler::DestroyPlayer(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "Got DestroyPlayer RPC from server");
}

void CClientRPCHandler::ChatInput(CBitStreamInterface * pBitStream, EntityId playerId)
{
	// Read the data the server sent us
	EntityId inputPlayerId;
	String strInput;

	// Read the input player id
	if(!pBitStream->ReadCompressed(inputPlayerId))
		return;

	// Read the input
	if(!pBitStream->Read(strInput))
		return;

	// Set the message name to default
	String strMessageName = "Invalid player";

	// Get the network player pointer
	CNetworkPlayer * pPlayer = g_pClient->GetPlayerManager()->Get(playerId);

	// Is the network player pointer valid?
	if(pPlayer)
	{
		// Set the message name
		strMessageName = pPlayer->GetName();
	}
	// Is the input from ourselves?
	else if(inputPlayerId == g_pClient->GetPlayerManager()->GetLocalId())
	{
		strMessageName = g_pClient->GetNick();
	}

	// TODO: MESSAGE_CHAT_COLOR
	g_pClient->GetChatWindow()->OutputMessage(MESSAGE_INFO_COLOR, "%s (Id: %d): %s (%d)", strMessageName.C_String(), inputPlayerId, strInput.C_String(), strInput.GetLength());
}

void CClientRPCHandler::Register()
{
	AddFunction(RPC_INITIAL_DATA, InitialData);
	AddFunction(RPC_ADD_PLAYER, AddPlayer);
	AddFunction(RPC_DELETE_PLAYER, DeletePlayer);
	AddFunction(RPC_SPAWN_PLAYER, SpawnPlayer);
	AddFunction(RPC_DESTROY_PLAYER, DestroyPlayer);
	AddFunction(RPC_CHAT_INPUT, ChatInput);
}

void CClientRPCHandler::Unregister()
{
	RemoveFunction(RPC_INITIAL_DATA);
	RemoveFunction(RPC_ADD_PLAYER);
	RemoveFunction(RPC_DELETE_PLAYER);
	RemoveFunction(RPC_SPAWN_PLAYER);
	RemoveFunction(RPC_DESTROY_PLAYER);
	RemoveFunction(RPC_CHAT_INPUT);
}
