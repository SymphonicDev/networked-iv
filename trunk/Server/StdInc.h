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
#include <time.h>
#include <queue>

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
#include <TinyXML/tinyxml.h>
#include <TinyXML/ticpp.h>
#include <CXML.h>
#include <CMutex.h>
#include <CThread.h>

// Project
#include "CConfig.h"
#include "CServer.h"
#include "CServerRPCHandler.h"
#include "CServerPacketHandler.h"
#include "CNetworkManager.h"
#include "CPlayer.h"
#include "CPlayerManager.h"
