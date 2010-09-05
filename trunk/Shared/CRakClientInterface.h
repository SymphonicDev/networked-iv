//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CRakClientInterface.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CRakClientInterface
{
public:
	virtual bool               Startup(String strEncryptionKeyE = "", String strEncryptionKeyModulus = "") = 0;
	virtual void               Shutdown(int iBlockDuration) = 0;
	virtual bool               Connect() = 0;
	virtual void               Disconnect() = 0;
	virtual void               SetPassword(String strPassword) = 0;
	virtual String             GetPassword() = 0;
	virtual unsigned int       Send(CBitStreamInterface * bsData, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel = 0) = 0;
	virtual unsigned int       RPC(RPCIdentifier rpcId, CBitStreamInterface * bsData, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel = 0) = 0;
	virtual void               SetHost(String strHost) = 0;
	virtual String             GetHost() = 0;
	virtual void               SetPort(unsigned short usPort) = 0;
	virtual unsigned short     GetPort() = 0;
	virtual bool               IsConnected() = 0;
	virtual CPacket *          Receive() = 0;
	virtual void               DeallocatePacket(CPacket * pPacket) = 0;
};
