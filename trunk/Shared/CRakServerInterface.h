//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CRakServerInterface.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CRakServerInterface
{
public:
	virtual bool               Startup(unsigned short usPort, int iMaxPlayers, String strHostAddress = "", int iThreadSleepTimer = 10) = 0;
	virtual void               Shutdown(int iBlockDuration) = 0;
	virtual void               SetPassword(String strPassword) = 0;
	virtual String             GetPassword() = 0;
	virtual unsigned int       Send(CBitStreamInterface * bsData, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel = 0) = 0;
	virtual unsigned int       RPC(RPCIdentifier rpcId, CBitStreamInterface * bsData, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel = 0) = 0;
	virtual CPacket *          Receive() = 0;
	virtual void               DeallocatePacket(CPacket * pPacket) = 0;
	virtual const char *       GetPlayerIp(EntityId playerId) = 0;
	virtual unsigned short     GetPlayerPort(EntityId playerId) = 0;
};
