//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CServerRPCHandler.h
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CServerRPCHandler : public CRPCHandler
{
private:
	static void InitialData(CBitStreamInterface * pBitStream, EntityId playerId);
	static void ChatInput(CBitStreamInterface * pBitStream, EntityId playerId);

public:
	void        Register();
	void        Unregister();
};

