//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetworkManager.cpp
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CNetworkManager::CNetworkManager()
{
	// Create the RakServer instance
	m_pRakServer = CNetModule::GetRakServerInterface();

	// Create the packet handler instance
	m_pServerPacketHandler = new CServerPacketHandler();

	// Create the rpc handler instance
	m_pServerRPCHandler = new CServerRPCHandler();
}

CNetworkManager::~CNetworkManager()
{
	// Unregister the rpcs
	m_pServerRPCHandler->Unregister();

	// Delete the rpc handler instance
	SAFE_DELETE(m_pServerRPCHandler);

	// Unregister the packets
	m_pServerPacketHandler->Unregister();

	// Delete the packet handler instance
	SAFE_DELETE(m_pServerPacketHandler);

	// Shutdown the RakServer instance
	m_pRakServer->Shutdown(500);

	// Delete the RakServer instance
	CNetModule::DestroyRakServerInterface(m_pRakServer);
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

	// Register the packets
	m_pServerPacketHandler->Register();

	// Register the rpcs
	m_pServerRPCHandler->Register();
}

void CNetworkManager::Process()
{
	CPacket * pPacket = NULL;

	// Loop until we have processed all packets in the packet queue (if any)
	while(pPacket = m_pRakServer->Receive())
	{
		printf("Got packet %d from player %d\n", pPacket->packetId, pPacket->playerId);

		// Pass it to the packet handler, if that doesn't handle it, pass it to the rpc handler
		if(!m_pServerPacketHandler->HandlePacket(pPacket) && !m_pServerRPCHandler->HandlePacket(pPacket))
		{
#ifdef _DEBUG
			CLogFile::Printf("Warning: Unhandled packet (Id: %d, Player: %d)", pPacket->packetId, pPacket->playerId);
#endif
		}

		// Deallocate the packet memory used
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
