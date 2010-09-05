//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: StdInc.h
// Project: Server
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

// Default
#ifdef WIN32
#include <windows.h>
#else
#include <Linux.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <list>
#include <map>
#include <string>

// Shared
#include <Common.h>
#include <CString.h>
#include <SharedUtility.h>
#include <CPacket.h>
#include <PacketIdentifiers.h>
#include <PacketPriorities.h>
#include <PacketReliabilities.h>
#include <RPCIdentifiers.h>
#include <CNetBitStreamInterface.h>
#include <CBitStreamInterface.h>
#include <CBitStream.h>
#include <CRPCHandler.h>
#include <CRakServerInterface.h>
#include <CRakClientInterface.h>
#include <CLibrary.h>
#include <CNetModule.h>
#include <CLogFile.h>

// Project
#include "CServer.h"
#include "CServerRPCs.h"
#include "CServerPacketHandler.h"
#include "CNetworkManager.h"
#include "CPlayer.h"
#include "CPlayerManager.h"
