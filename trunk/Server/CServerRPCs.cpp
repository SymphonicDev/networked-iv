//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CServerRPCs.cpp
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CNetworkManager * g_pNetworkManager;
extern CPlayerManager *  g_pPlayerManager;

void CServerRPCs::InitialData(CBitStreamInterface * pBitStream, EntityId playerId)
{
	CLogFile::Printf("Got InitialData RPC from player %d", playerId);

	// Read the data they sent us
	String strName;
	
	// Read the name
	if(!pBitStream->Read(strName))
		return;

	// Add them to the player manager
	g_pPlayerManager->Add(playerId, strName);

	// Construct the initial data bit stream
	CBitStream bitStream;

	// Write their player id
	bitStream.WriteCompressed(playerId);

	// Send the initial data bit stream
	g_pNetworkManager->RPC(RPC_INITIAL_DATA, &bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, playerId, false);

	// Send them all current players
	g_pPlayerManager->HandlePlayerJoin(playerId);

	CLogFile::Printf("Player %d has joined the game (Name: %s)", playerId, strName.C_String());
}

void CServerRPCs::ChatInput(CBitStreamInterface * pBitStream, EntityId playerId)
{
	CLogFile::Printf("Got ChatInput RPC from player %d", playerId);

	// Read the data they sent us
	bool bIsCommand;
	String strInput;

	// Read if its a command or not
	bIsCommand = pBitStream->ReadBit();

	// Read the input
	if(!pBitStream->Read(strInput))
		return;

	// Is it not a command?
	if(!bIsCommand)
	{
		// Construct the chat input bit stream
		CBitStream bitStream;

		// Write the player id
		bitStream.WriteCompressed(playerId);

		// Write the input
		bitStream.Write(strInput);

		// Send it to all other players
		g_pNetworkManager->RPC(RPC_CHAT_INPUT, &bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, INVALID_ENTITY_ID, true);
	}

	CLogFile::Printf("Recieved chat input from player %d (Command?: %s, Input: %s)", playerId, bIsCommand ? "Yes" : "No", strInput.C_String());
}

void CServerRPCs::Register(CRPCHandler * pRPCHandler)
{
	CLogFile::Printf("Registering server RPCs");
	pRPCHandler->AddFunction(RPC_INITIAL_DATA, InitialData);
	pRPCHandler->AddFunction(RPC_CHAT_INPUT, ChatInput);
	CLogFile::Printf("Server RPCs registered");
}

void CServerRPCs::Unregister(CRPCHandler * pRPCHandler)
{
	CLogFile::Printf("Unregistering server RPCs");
	pRPCHandler->RemoveFunction(RPC_INITIAL_DATA);
	pRPCHandler->RemoveFunction(RPC_CHAT_INPUT);
	CLogFile::Printf("Server RPCs unregistered");
}
