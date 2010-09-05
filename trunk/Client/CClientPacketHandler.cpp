//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPacketHandler.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

// TODO: Shared packet handler then CClient/ServerPackets (Like the RPC system)

#include <StdInc.h>

extern CClient * g_pClient;
extern CNetworkManager * g_pNetworkManager;
extern CChatWindow * g_pChatWindow;

CPacketHandler::CPacketHandler()
{

}

CPacketHandler::~CPacketHandler()
{

}

void CPacketHandler::ConnectionSucceeded(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Connection established!");

	// Construct the initial data bit stream
	CBitStream bitStream;

	// Write the name
	bitStream.Write(g_pClient->GetNick());

	// Send the initial data bit stream
	g_pNetworkManager->RPC(RPC_INITIAL_DATA, &bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED);
}

void CPacketHandler::ConnectionFailed(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Connection failed! (Timeout)");
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Retrying...");
	g_pNetworkManager->Connect();
}

void CPacketHandler::AlreadyConnected(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Connection failed! (Already Connected)");
	g_pNetworkManager->Disconnect();
}

void CPacketHandler::ServerFull(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Connection failed! (Server Full)");
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Retrying...");
	g_pNetworkManager->Connect();
}

void CPacketHandler::Disconnected(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Disconnected from the server.");
	g_pNetworkManager->Disconnect();
}

void CPacketHandler::LostConnection(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Connection to server lost!");
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Reconnecting...");
	g_pNetworkManager->Connect();
}

void CPacketHandler::Banned(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Connection failed! (Banned)");
	g_pNetworkManager->Disconnect();
}

void CPacketHandler::PasswordInvalid(CBitStreamInterface * pBitStream, EntityId playerId)
{
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Connection failed! (Invalid Password)");
	g_pNetworkManager->Disconnect();
}

bool CPacketHandler::HandlePacket(CPacket * pPacket)
{
	// Construct the packet BitStream
	CBitStream bitStream(pPacket->ucData, pPacket->uLength, false);

	// See if we can handle the packet
	switch(pPacket->packetId)
	{
	case PACKET_CONNECTION_SUCCEEDED:
		ConnectionSucceeded(&bitStream, pPacket->playerId);
		return true;
		break;
	case PACKET_CONNECTION_FAILED:
		ConnectionFailed(&bitStream, pPacket->playerId);
		return true;
		break;
	case PACKET_ALREADY_CONNECTED:
		AlreadyConnected(&bitStream, pPacket->playerId);
		return true;
		break;
	case PACKET_SERVER_FULL:
		ServerFull(&bitStream, pPacket->playerId);
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
	case PACKET_BANNED:
		Banned(&bitStream, pPacket->playerId);
		return true;
		break;
	case PACKET_PASSWORD_INVALID:
		PasswordInvalid(&bitStream, pPacket->playerId);
		return true;
		break;
	}

	// Not handled
	return false;
}
