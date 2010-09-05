//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CServerRPCs.h
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CServerRPCs
{
private:
	static void InitialData(CBitStreamInterface * pBitStream, EntityId playerId);
public:
	static void Register(CRPCHandler * pRPCHandler);
	static void Unregister(CRPCHandler * pRPCHandler);
};

