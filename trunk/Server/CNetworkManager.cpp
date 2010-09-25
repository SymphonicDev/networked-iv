//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetworkManager.cpp
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CNetModule * g_pNetModule;

CNetworkManager::CNetworkManager()
{
	// Create the RakServer instance
	m_pRakServer = g_pNetModule->GetRakServerInterface();

	// Create the rpc handler instance
	m_pServerRPCHandler = new CServerRPCHandler();

	// Create the packet handler instance
	m_pPacketHandler = new CPacketHandler();
}

CNetworkManager::~CNetworkManager()
{
	// Delete the packet handler instance
	SAFE_DELETE(m_pPacketHandler);

	// Delete the rpc handler instance
	SAFE_DELETE(m_pServerRPCHandler);

	// Shutdown the RakServer instance
	m_pRakServer->Shutdown(500);

	// Delete the RakServer instance
	g_pNetModule->DestroyRakServerInterface(m_pRakServer);
}

void CNetworkManager::Startup(int iPort, int iMaxPlayers, String strPassword, String strHostAddress)
{
	// Start up the RakServer
	m_pRakServer->Startup(iPort, iMaxPlayers, strHostAddress.C_String());

	// Do we have a password?
	if(!strPassword.IsEmpty())
	{
		// Set the RakServer password
		m_pRakServer->SetPassword(strPassword.C_String());
	}

	// Register the rpcs
	m_pServerRPCHandler->Register();
}

void CNetworkManager::Process()
{
	CPacket * pPacket;
	
	while(pPacket = m_pRakServer->Receive())
	{
		printf("Got packet %d from player %d\n", pPacket->packetId, pPacket->playerId);

		// Pass it to the rpc handler
		if(!m_pServerRPCHandler->HandlePacket(pPacket))
		{
			// The rpc handler didn't handler it, pass it to the packet handler
			if(!m_pPacketHandler->HandlePacket(pPacket))
			{
#ifdef _DEBUG
				CLogFile::Printf("Warning: Unhandled packet (Id: %d)\n", pPacket->packetId);
#endif
			}
		}

		m_pRakServer->DeallocatePacket(pPacket);
	}
}

void CNetworkManager::RPC(RPCIdentifier rpcId, CBitStreamInterface * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel)
{
	m_pRakServer->RPC(rpcId, pBitStream, priority, reliability, playerId, bBroadcast, cOrderingChannel);
}

const char * CNetworkManager::GetPlayerIp(EntityId playerId)
{
	return m_pRakServer->GetPlayerIp(playerId);
}

unsigned short CNetworkManager::GetPlayerPort(EntityId playerId)
{
	return m_pRakServer->GetPlayerPort(playerId);
}
