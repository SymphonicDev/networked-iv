//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CClientPacketHandler.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CClientPacketHandler : public CPacketHandler
{
private:
	static void ConnectionSucceeded(CBitStreamInterface * pBitStream, EntityId playerId);
	static void ConnectionFailed(CBitStreamInterface * pBitStream, EntityId playerId);
	static void AlreadyConnected(CBitStreamInterface * pBitStream, EntityId playerId);
	static void ServerFull(CBitStreamInterface * pBitStream, EntityId playerId);
	static void Disconnected(CBitStreamInterface * pBitStream, EntityId playerId);
	static void LostConnection(CBitStreamInterface * pBitStream, EntityId playerId);
	static void Banned(CBitStreamInterface * pBitStream, EntityId playerId);
	static void PasswordInvalid(CBitStreamInterface * pBitStream, EntityId playerId);

public:
	void        Register();
	void        Unregister();
};
