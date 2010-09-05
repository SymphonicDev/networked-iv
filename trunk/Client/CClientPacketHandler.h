//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPacketHandler.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CPacketHandler
{
private:
	void ConnectionSucceeded(CBitStreamInterface * pBitStream, EntityId playerId);
	void ConnectionFailed(CBitStreamInterface * pBitStream, EntityId playerId);
	void AlreadyConnected(CBitStreamInterface * pBitStream, EntityId playerId);
	void ServerFull(CBitStreamInterface * pBitStream, EntityId playerId);
	void Disconnected(CBitStreamInterface * pBitStream, EntityId playerId);
	void LostConnection(CBitStreamInterface * pBitStream, EntityId playerId);
	void Banned(CBitStreamInterface * pBitStream, EntityId playerId);
	void PasswordInvalid(CBitStreamInterface * pBitStream, EntityId playerId);

public:
	CPacketHandler();
	~CPacketHandler();

	bool HandlePacket(CPacket * pPacket);
};
