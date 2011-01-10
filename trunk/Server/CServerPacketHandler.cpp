//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CServerPacketHandler.cpp
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CNetworkManager * g_pNetworkManager;
extern CPlayerManager * g_pPlayerManager;

void CServerPacketHandler::NewConnection(CBitStreamInterface * pBitStream, EntityId playerId)
{
	CLogFile::Printf("New connection from ip %s (Port %d, Player %d)", g_pNetworkManager->GetPlayerIp(playerId), g_pNetworkManager->GetPlayerPort(playerId), playerId);
}

void CServerPacketHandler::Disconnected(CBitStreamInterface * pBitStream, EntityId playerId)
{
	CLogFile::Printf("Player %d disconnected", playerId);
	g_pPlayerManager->Delete(playerId);
}

void CServerPacketHandler::LostConnection(CBitStreamInterface * pBitStream, EntityId playerId)
{
	CLogFile::Printf("Player %d lost connection", playerId);
	g_pPlayerManager->Delete(playerId);
}

void CServerPacketHandler::Register()
{
	AddFunction(PACKET_NEW_CONNECTION, NewConnection);
	AddFunction(PACKET_DISCONNECTED, Disconnected);
	AddFunction(PACKET_LOST_CONNECTION, LostConnection);
}

void CServerPacketHandler::Unregister()
{
	RemoveFunction(PACKET_NEW_CONNECTION);
	RemoveFunction(PACKET_DISCONNECTED);
	RemoveFunction(PACKET_LOST_CONNECTION);
}
