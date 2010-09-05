//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetworkManager.h
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CNetworkManager
{
private:
	CRakServerInterface * m_pRakServer;
	CRPCHandler * m_pRPCHandler;
	CPacketHandler * m_pPacketHandler;

public:
	CNetworkManager();
	~CNetworkManager();

	void           Startup(int iPort, int iMaxPlayers, String strPassword = "", String strHostAddress = "");
	void           Process();
	void           RPC(RPCIdentifier rpcId, CBitStreamInterface * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel = 0);
	const char *   GetPlayerIp(EntityId playerId);
	unsigned short GetPlayerPort(EntityId playerId);
};