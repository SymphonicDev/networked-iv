//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CServerPacketHandler.h
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CServerPacketHandler : public CPacketHandler
{
private:
	static void NewConnection(CBitStreamInterface * pBitStream, EntityId playerId);
	static void Disconnected(CBitStreamInterface * pBitStream, EntityId playerId);
	static void LostConnection(CBitStreamInterface * pBitStream, EntityId playerId);

public:
	void        Register();
	void        Unregister();
};
