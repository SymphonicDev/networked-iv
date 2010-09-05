//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPacketHandler.cpp
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CNetworkManager * g_pNetworkManager;
extern CPlayerManager * g_pPlayerManager;

CPacketHandler::CPacketHandler()
{

}

CPacketHandler::~CPacketHandler()
{

}

void CPacketHandler::NewConnection(CBitStreamInterface * pBitStream, EntityId playerId)
{
	CLogFile::Printf("New connection from ip %s (Port %d, Player %d)", g_pNetworkManager->GetPlayerIp(playerId), g_pNetworkManager->GetPlayerPort(playerId), playerId);
}

void CPacketHandler::Disconnected(CBitStreamInterface * pBitStream, EntityId playerId)
{
	CLogFile::Printf("Player %d disconnected", playerId);
	g_pPlayerManager->Delete(playerId);
}

void CPacketHandler::LostConnection(CBitStreamInterface * pBitStream, EntityId playerId)
{
	CLogFile::Printf("Player %d lost connection", playerId);
	g_pPlayerManager->Delete(playerId);
}

bool CPacketHandler::HandlePacket(CPacket * pPacket)
{
	// Construct the packet BitStream
	CBitStream bitStream(pPacket->ucData, pPacket->uLength, false);

	// See if we can handle the packet
	switch(pPacket->packetId)
	{
	case PACKET_NEW_CONNECTION:
		NewConnection(&bitStream, pPacket->playerId);
		return true;
		break;
	case PACKET_DISCONNECTED:
		Disconnected(&bitStream, pPacket->playerId);
		return true;
		break;
	case PACKET_LOST_CONNECTION:
		LostConnection(&bitStream, pPacket->playerId);
		return true;
		break;
	}

	// Not handled
	return false;
}
