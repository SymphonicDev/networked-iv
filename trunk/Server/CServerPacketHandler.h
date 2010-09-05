//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPacketHandler.h
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CPacketHandler
{
private:
	void NewConnection(CBitStreamInterface * pBitStream, EntityId playerId);
	void Disconnected(CBitStreamInterface * pBitStream, EntityId playerId);
	void LostConnection(CBitStreamInterface * pBitStream, EntityId playerId);

public:
	CPacketHandler();
	~CPacketHandler();

	bool HandlePacket(CPacket * pPacket);
};
