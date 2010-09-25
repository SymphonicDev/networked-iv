//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: StdInc.h
// Project: Client
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

// Default
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <detours.h>
#include <list>
#include <string>
#include <time.h>

// Shared
#include <Common.h>
#include <CString.h>
#include <SharedUtility.h>
#include <CPatcher.h>
#include <CPacket.h>
#include <PacketIdentifiers.h>
#include <PacketPriorities.h>
#include <PacketReliabilities.h>
#include <RPCIdentifiers.h>
#include <CNetBitStreamInterface.h>
#include <CBitStreamInterface.h>
#include <CBitStream.h>
#include <CRPCHandler.h>
#include <CRakClientInterface.h>
#include <CRakServerInterface.h>
#include <CLibrary.h>
#include <CNetModule.h>
#include <CLogFile.h>

// Project
#include "CClient.h"
#include "CDirect3D9Hook.h"
#include "CDirect3D9Proxy.h"
#include "CDirect3DDevice9Proxy.h"
#include "CWindowSubclass.h"
#include "CXLiveHook.h"
#include "CFont.h"
#include "CD3DXFont.h"
#include "CChatLine.h"
#include "CChatWindow.h"

// IV
#include "IVCommon.h"
#include "NativeContext.h"
#include "InvokeNative.h"
#include "CIVEntity.h"
#include "CIVDynamicEntity.h"
#include "CIVPhysical.h"
#include "CIVPed.h"
#include "CIVPlayerPed.h"
#include "CIVPlayerInfo.h"
#include "CPools.h"
#include "CIVWorld.h"
#include "CPlayer.h"
#include "CGame.h"

// Project
#include "CBitStream.h"
#include "CClientRPCHandler.h"
#include "CClientPacketHandler.h"
#include "CNetworkManager.h"
#include "CLocalPlayer.h"
#include "CNetworkPlayer.h"
#include "CPlayerManager.h"
