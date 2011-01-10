//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetworkManager.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CClient * g_pClient;

CNetworkManager::CNetworkManager()
{
	// Create the RakClient instance
	m_pRakClient = CNetModule::GetRakClientInterface();

	// Create the packet handler instance
	m_pClientPacketHandler = new CClientPacketHandler();

	// Create the rpc handler instance
	m_pClientRPCHandler = new CClientRPCHandler();
}

CNetworkManager::~CNetworkManager()
{
	// Unregister the rpcs
	m_pClientRPCHandler->Unregister();

	// Delete the rpc handler instance
	SAFE_DELETE(m_pClientRPCHandler);

	// Unregister the packets
	m_pClientPacketHandler->Unregister();

	// Delete the packet handler instance
	SAFE_DELETE(m_pClientPacketHandler);

	// Shutdown the RakClient instance
	m_pRakClient->Shutdown(500);

	// Destroy the RakClient instance
	CNetModule::DestroyRakClientInterface(m_pRakClient);
}

void CNetworkManager::Startup(String strHost, unsigned short usPort, String strPassword)
{
	// Start up the RakClient
	m_pRakClient->Startup();

	// Set the RakClient host
	m_pRakClient->SetHost(strHost);

	// Set the RakClient port
	m_pRakClient->SetPort(usPort);

	// Do we have a password?
	if(!strPassword.IsEmpty())
	{
		// Set the RakClient password
		m_pRakClient->SetPassword(strPassword);
	}

	// Register the packets
	m_pClientPacketHandler->Register();

	// Register the rpcs
	m_pClientRPCHandler->Register();
}

void CNetworkManager::Process()
{
	CPacket * pPacket = NULL;

	// Loop until we have processed all packets in the packet queue (if any)
	while(pPacket = m_pRakClient->Receive())
	{
		// Pass it to the packet handler, if that doesn't handle it, pass it to the rpc handler
		if(!m_pClientPacketHandler->HandlePacket(pPacket) && !m_pClientRPCHandler->HandlePacket(pPacket))
		{
#ifdef _DEBUG
			CLogFile::Printf("Warning: Unhandled packet (Id: %d)", pPacket->packetId);
#endif
		}

		// Deallocate the packet memory used
		m_pRakClient->DeallocatePacket(pPacket);
	}
}

void CNetworkManager::Connect()
{
	// Are we not already connected?
	if(!IsConnected())
	{
		// Start the RakClient connection process
		m_pRakClient->Connect();
	}
}

bool CNetworkManager::IsConnected()
{
	return m_pRakClient->IsConnected();
}

void CNetworkManager::Disconnect()
{
	// Are we connected?
	if(IsConnected())
	{
		// Disconnect from the server
		m_pRakClient->Disconnect();
	}
}

void CNetworkManager::RPC(RPCIdentifier rpcId, CBitStreamInterface * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel)
{
	m_pRakClient->RPC(rpcId, pBitStream, priority, reliability, cOrderingChannel);
}
