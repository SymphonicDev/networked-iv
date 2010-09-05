//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPools.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CClient * g_pClient;

unsigned int CPools::GetHandleFromPed(IVPed * pPed)
{
	DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CPool__HandleOf_7);
	DWORD dwPedPool = (g_pClient->GetBaseAddress() + VAR_PedPool_7);
	unsigned int uiHandle = 0;
	_asm
	{
		mov ecx, dwPedPool
		push pPed
		call dwFunc
		mov uiHandle, eax
	}
	return uiHandle;
}

IVPed * CPools::GetPedFromHandle(unsigned int uiHandle)
{
	DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CPool__AtHandle_7);
	DWORD dwPedPool = (g_pClient->GetBaseAddress() + VAR_PedPool_7);
	IVPed * pPed = NULL;
	_asm
	{
		mov ecx, dwPedPool
		push uiHandle
		call dwFunc
		mov pPed, eax
	}
	return pPed;
}

unsigned int CPools::GetHandleFromVehicle(DWORD dwVehicle)
{
	DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CPool__HandleOf_7);
	DWORD dwVehiclePool = (g_pClient->GetBaseAddress() + VAR_VehiclePool_7);
	unsigned int uiHandle = 0;
	_asm
	{
		mov ecx, dwVehiclePool
		push dwVehicle
		call dwFunc
		mov uiHandle, eax
	}
	return uiHandle;
}

DWORD CPools::GetVehicleFromHandle(unsigned int uiHandle)
{
	DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CPool__AtHandle_7);
	DWORD dwVehiclePool = (g_pClient->GetBaseAddress() + VAR_VehiclePool_7);
	DWORD dwVehicle = NULL;
	_asm
	{
		mov ecx, dwVehiclePool
		push uiHandle
		call dwFunc
		mov dwVehicle, eax
	}
	return dwVehicle;
}

IVPlayerPed * CPools::GetPlayerPedFromIndex(unsigned int uiIndex)
{
	// Is the index more than the player ped array size?
	if(uiIndex > PLAYER_PED_ARRAY_SIZE)
		return NULL;

	// Get the player ped pointer array
	IVPlayerPed ** pPlayerPeds = (IVPlayerPed **)(g_pClient->GetBaseAddress() + VAR_PlayerPedArray);

	// Return the player ped pointer
	return pPlayerPeds[uiIndex];
}

IVPlayerPed * CPools::GetPlayerPedFromPed(IVPed * pPed)
{
	// Loop through all player ped indexes
	for(unsigned int i = 0; i < PLAYER_PED_ARRAY_SIZE; i++)
	{
		// Get the current player ped
		IVPlayerPed * pPlayerPed = GetPlayerPedFromIndex(i);

		// Does the current player ped exist?
		if(pPlayerPed)
		{
			// Is the current player peds ped the ped?
			if(pPlayerPed->m_pPed == pPed)
				return pPlayerPed;
		}
	}

	return NULL;
}

unsigned int CPools::GetIndexFromPlayerPed(IVPlayerPed * pPlayerPed)
{
	// Loop through all player ped indexes
	for(unsigned int i = 0; i < PLAYER_PED_ARRAY_SIZE; i++)
	{
		// Is the current index the player ped?
		if(GetPlayerPedFromIndex(i) == pPlayerPed)
			return i;
	}

	// Player ped not found in array
	return INVALID_PLAYER_PED;
}

void CPools::SetPlayerPedAtIndex(unsigned int uiIndex, IVPlayerPed * pPlayerPed)
{
	// Is the index more than the player ped array size?
	if(uiIndex > PLAYER_PED_ARRAY_SIZE)
		return;

	// Get the player ped pointer array
	IVPlayerPed ** pPlayerPeds = (IVPlayerPed **)(g_pClient->GetBaseAddress() + VAR_PlayerPedArray);

	// Set the player ped pointer
	pPlayerPeds[uiIndex] = pPlayerPed;
}

unsigned int CPools::FindFreePlayerPedIndex()
{
	// Loop through all player ped indexes
	for(unsigned int i = 0; i < PLAYER_PED_ARRAY_SIZE; i++)
	{
		// Is the current index free?
		if(!GetPlayerPedFromIndex(i))
			return i;
	}

	// No free player ped indexes found
	return INVALID_PLAYER_PED;
}

unsigned int CPools::GetLocalPlayerIndex()
{
	return *(unsigned int *)(g_pClient->GetBaseAddress() + VAR_LocalPlayerId_7);
}

void CPools::SetLocalPlayerIndex(unsigned int uiIndex)
{
	*(unsigned int *)(g_pClient->GetBaseAddress() + VAR_LocalPlayerId_7) = uiIndex;
}
