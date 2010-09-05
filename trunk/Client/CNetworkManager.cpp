//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetworkManager.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CNetModule * g_pNetModule;

CNetworkManager::CNetworkManager()
{
	// Create the RakClient instance
	m_pRakClient = g_pNetModule->GetRakClientInterface();

	// Create the rpc handler instance
	m_pRPCHandler = new CRPCHandler();

	// Create the packet handler instance
	m_pPacketHandler = new CPacketHandler();
}

CNetworkManager::~CNetworkManager()
{
	// Delete the packet handler instance
	SAFE_DELETE(m_pPacketHandler);

	// Delete the rpc handler instance
	SAFE_DELETE(m_pRPCHandler);

	// Shutdown the RakClient instance
	m_pRakClient->Shutdown(500);

	// Destroy the RakClient instance
	g_pNetModule->DestroyRakClientInterface(m_pRakClient);
}

void CNetworkManager::Startup(String strHost, unsigned short usPort, String strPassword)
{
	// Start up the RakClient
	m_pRakClient->Startup();

	// Set the RakClient host
	m_pRakClient->SetHost(strHost.C_String());

	// Set the RakClient port
	m_pRakClient->SetPort(usPort);

	// Do we have a password?
	if(!strPassword.IsEmpty())
	{
		// Set the RakClient password
		m_pRakClient->SetPassword(strPassword.C_String());
	}

	// Register the rpcs
	CClientRPCs::Register(m_pRPCHandler);
}

void CNetworkManager::Process()
{
	CPacket * pPacket;

	while(pPacket = m_pRakClient->Receive())
	{
		// Pass it to the rpc handler
		if(!m_pRPCHandler->HandlePacket(pPacket))
		{
			// The rpc handler didn't handle it, pass it to the packet handler
			if(!m_pPacketHandler->HandlePacket(pPacket))
			{
#ifdef _DEBUG
				CLogFile::Printf("Warning: Unhandled packet (Id: %d)\n", pPacket->packetId);
#endif
			}
		}

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
