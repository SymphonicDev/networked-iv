//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPlayer.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

#define MODEL_PLAYER 0x6F0783F5

extern CClient * g_pClient;

// Quick And Hacky Player Ped Slot Code
bool bInitQuickAndHackyPlayerPedSlotCode = false;
BYTE byteFreePlayerPedSlots[32];

void InitQuickAndHackyPlayerPedSlotCode()
{
	if(!bInitQuickAndHackyPlayerPedSlotCode)
	{
		byteFreePlayerPedSlots[0] = 1;
		for(BYTE i = 1; i < 32; i++)
		{
			byteFreePlayerPedSlots[i] = 0;
		}
		bInitQuickAndHackyPlayerPedSlotCode = true;
	}
}

BYTE FindQuickAndHackyPlayerPedSlot()
{
	if(bInitQuickAndHackyPlayerPedSlotCode)
	{
		for(BYTE i = 1; i < 32; i++)
		{
			if(!byteFreePlayerPedSlots[i])
			{
				return i;
			}
		}
	}

	return INVALID_PLAYER_PED;
}

void SetQuickAndHackyPlayerPedSlot(BYTE byteSlot, BYTE byteStatus)
{
	byteFreePlayerPedSlots[byteSlot] = byteStatus;
}
// End Quick And Hacky Player Ped Slot Code

CPlayer::CPlayer(bool bLocalPlayer)
{
	InitQuickAndHackyPlayerPedSlotCode();
	if(bLocalPlayer)
	{
		// Set the player index to local player index
		m_uiPlayerIndex = CPools::GetLocalPlayerIndex();

		// Create the player ped instance with the local player ped pointer
		m_pPlayerPed = new CIVPlayerPed(CPools::GetPlayerInfoFromIndex(0)->m_pPlayerPed);

		// Set the model hash to the default player model hash
		m_dwModelHash = MODEL_PLAYER;
	}
	else
	{
		// Invalidate the player index
		m_uiPlayerIndex = -1;

		// Set the player ped instance to NULL
		m_pPlayerPed = NULL;

		// Set the model hash to the default player model hash
		m_dwModelHash = MODEL_PLAYER;
	}
}

CPlayer::~CPlayer()
{
	// Are we spawned and not the local player?
	if(IsSpawned() && !IsLocalPlayer())
	{
		// Destroy ourselves
		Destroy();
	}
}

bool CPlayer::IsLocalPlayer()
{
	// TODO: Use the internal local player index here?
	return (m_uiPlayerIndex == 0);
}

bool CPlayer::IsSpawned()
{
	// Is the player ped instance valid?
	return (m_pPlayerPed != NULL);
}

// TODO: Use this to create local player ped too instead of using scripting natives?
bool CPlayer::Create()
{
	// Are we not already created?
	if(!IsSpawned())
	{
		// Find a free player info index
		m_uiPlayerIndex = FindQuickAndHackyPlayerPedSlot();

		CLogFile::Printf("PlayerPed: %d, LocalPlayerPed: %d, LocalPlayerPointer: 0x%p", m_uiPlayerIndex, CPools::GetLocalPlayerIndex(), CPools::GetPlayerInfoFromIndex(0)->m_pPlayerPed);

		// Invalid player info index?
		if(m_uiPlayerIndex == INVALID_PLAYER_PED)
			return false;

		// Load model (if needed) and get model index
		int iModelIndex = g_pClient->GetGame()->LoadModel(m_dwModelHash);

		// Invalid model hash?
		if(iModelIndex == -1)
			return false;

		// Save the local player index
		unsigned int uiLocalPlayerIndex = CPools::GetLocalPlayerIndex();

		// Create player ped
		DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CreatePlayerPed_7);
		unsigned int uiPlayerIndex = m_uiPlayerIndex;
		WORD wPlayerData = MAKEWORD(0, 1);
		WORD * pwPlayerData = &wPlayerData;
		IVPlayerPed * pPlayerPed = NULL;
		_asm
		{
			push 0 ; unknown
			push iModelIndex ; model index
			push uiPlayerIndex ; player index
			push pwPlayerData ; unknown
			call dwFunc
			mov pPlayerPed, eax
			add esp, 10h
		}

		// Restore the local player index
		CPools::SetLocalPlayerIndex(uiLocalPlayerIndex);

		// Invalid player ped?
		if(!pPlayerPed)
			return false;

		// Setup ped intelligence
		dwFunc = (g_pClient->GetBaseAddress() + FUNC_SetupPedIntelligence_7);
		_asm
		{
			push 2 ; unknown
			mov ecx, pPlayerPed
			call dwFunc
		}

		// Create player ped
		m_pPlayerPed = new CIVPlayerPed(pPlayerPed);

		// Get scripting handle
		m_uiScriptingHandle = CPools::GetHandleFromPed((IVPed *)pPlayerPed);

		CLogFile::Printf("Handle is %d", m_uiScriptingHandle);

		// Add to world
		m_pPlayerPed->AddToWorld();

		// Set health
		//SetHealth(200);

		// Set free slot
		SetQuickAndHackyPlayerPedSlot(m_uiPlayerIndex, 1);

		// Testing code
		InvokeNative<void *>(0x575E2880, m_uiScriptingHandle, 200); // SET_CHAR_HEALTH
		InvokeNative<void *>(0x689D0F5F, m_uiScriptingHandle, -341.36f, 1144.80f, 14.79f); // SET_CHAR_COORDINATES
		InvokeNative<void *>(0x46B5523B, m_uiScriptingHandle, 40.114815f); // SET_CHAR_HEADING

		CLogFile::Printf("Done: PlayerPed: %d, LocalPlayerPed: %d, LocalPlayerPointer: 0x%p", m_uiPlayerIndex, CPools::GetLocalPlayerIndex(), CPools::GetPlayerInfoFromIndex(0)->m_pPlayerPed);

		return true;
	}

	// Already created
	return false;
}

void CPlayer::Destroy()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Remove the player ped from the world
		m_pPlayerPed->RemoveFromWorld();

		// Delete the player ped
		DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CPlayerPed__Destructor_7);
		IVPlayerPed * pPlayerPed = m_pPlayerPed->GetPlayerPed();
		_asm
		{
			push 1
			mov ecx, pPlayerPed
			call dwFunc
		}

		/*CLogFile::Printf("Deleting");

		// Delete the player info
		dwFunc = (g_pClient->GetBaseAddress() + FUNC_DeletePlayer);
		unsigned int uiPlayerIndex = m_uiPlayerIndex;
		_asm
		{
			push uiPlayerIndex
			call dwFunc
			add esp, 4
		}

		CLogFile::Printf("Deleted");*/

		// Delete the player ped instance
		delete m_pPlayerPed;

		// Set the player ped instance to NULL
		m_pPlayerPed = NULL;

		// Set free slot
		SetQuickAndHackyPlayerPedSlot(m_uiPlayerIndex, 0);

		// Invalidate the player index
		m_uiPlayerIndex = -1;
	}
}

bool CPlayer::SetModelByHash(DWORD dwModelHash)
{
	// Get the model index from the hash
	int iModelIndex = g_pClient->GetGame()->GetModelIndexByHash(dwModelHash);

	// Is the model index valid?
	if(iModelIndex != -1)
	{
		// Set the model hash
		m_dwModelHash = dwModelHash;

		// TODO: Set the player model and set default component variation
		return true;
	}

	// Invalid model hash
	return false;
}

DWORD CPlayer::GetModelHash()
{
	return m_dwModelHash;
}

// TODO: CPlayer::Teleport which also cancels tasks (Uses same code from SET_CHAR_COORDINATES native)
// TODO: CPlayer::WarpFromVehicleToPosition

bool CPlayer::SetPosition(Vector3 * vecPosition, bool bRemoveFromWorld)
{
	if(IsSpawned())
	{
		m_pPlayerPed->RemoveFromWorld();
		m_pPlayerPed->SetPosition(vecPosition);
		m_pPlayerPed->AddToWorld();
		return true;
	}

	return false;
}

bool CPlayer::GetPosition(Vector3 * vecPosition)
{
	if(IsSpawned())
	{
		m_pPlayerPed->GetPosition(vecPosition);
		return true;
	}

	return false;
}
