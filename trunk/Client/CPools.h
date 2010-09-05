//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPools.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

#define VAR_PedPool_7 0x18A82AC
#define VAR_VehiclePool_7 0x1619240
#define FUNC_CPool__AtHandle_7 0x426700
#define FUNC_CPool__HandleOf_7 0x447230
#define VAR_PlayerPedArray 0x11A7008
#define VAR_LocalPlayerId_7 0xF1CC68
#define PLAYER_PED_ARRAY_SIZE 32
#define INVALID_PLAYER_PED 255

class CPools
{
public:
	// Peds
	static unsigned int  GetHandleFromPed(IVPed * pPed);
	static IVPed *       GetPedFromHandle(unsigned int uiHandle);

	// Vehicles
	static unsigned int  GetHandleFromVehicle(DWORD dwVehicle);
	static DWORD         GetVehicleFromHandle(unsigned int uiHandle);

	// Player Peds (An array not a pool)
	static IVPlayerPed * GetPlayerPedFromIndex(unsigned int uiIndex);
	static IVPlayerPed * GetPlayerPedFromPed(IVPed * pPed);
	static unsigned int  GetIndexFromPlayerPed(IVPlayerPed * pPlayerPed);
	static void          SetPlayerPedAtIndex(unsigned int uiIndex, IVPlayerPed * pPlayerPed);
	static unsigned int  FindFreePlayerPedIndex();
	static unsigned int  GetLocalPlayerIndex();
	static void          SetLocalPlayerIndex(unsigned int uiIndex);
};
