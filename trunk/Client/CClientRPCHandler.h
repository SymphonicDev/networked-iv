//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CClientRPCHandler.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CClientRPCHandler : public CRPCHandler
{
private:
	static void InitialData(CBitStreamInterface * pBitStream, EntityId playerId);
	static void AddPlayer(CBitStreamInterface * pBitStream, EntityId playerId);
	static void DeletePlayer(CBitStreamInterface * pBitStream, EntityId playerId);
	static void SpawnPlayer(CBitStreamInterface * pBitStream, EntityId playerId);
	static void DestroyPlayer(CBitStreamInterface * pBitStream, EntityId playerId);
	static void ChatInput(CBitStreamInterface * pBitStream, EntityId playerId);

public:
	void        Register();
	void        Unregister();
};
