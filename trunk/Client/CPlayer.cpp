//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CPlayer.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CClient * g_pClient;
extern CGame *   g_pGame;

CPlayer::CPlayer(bool bLocalPlayer)
{
	if(bLocalPlayer)
	{
		// Set the player index to 0 (Local player)
		// TODO: Use the internal local player index here
		m_uiPlayerIndex = 0;

		// Create the player ped instance with the local player ped pointer
		m_pPlayerPed = new CIVPlayerPed(CPools::GetPlayerPedFromIndex(0));

		// Set the model hash to the default player model hash
		m_dwModelHash = 0x6F0783F5; // MODEL_PLAYER
	}
	else
	{
		// Find a free player ped index
		m_uiPlayerIndex = CPools::FindFreePlayerPedIndex();

		// Set the player ped instance to NULL
		m_pPlayerPed = NULL;

		// Set the model hash to the default player model hash
		m_dwModelHash = 0x6F0783F5; // MODEL_PLAYER
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

//#define ADDR_CreatePlayer_1_6 0x81CE07
#define ADDR_CreatePlayer_1_7 0x81CBC7
//#define FUNC_CreatePlayer_1_6 0x81CDD0
#define FUNC_CreatePlayer_1_7 0x81CB90
//#define FUNC_CreatePlayer_2_6 0x89EE30
#define FUNC_CreatePlayer_2_7 0x89EC20

bool CPlayer::Create()
{
	// Are we not already created?
	if(!IsSpawned())
	{
#if 0
		// Load the model (if needed)
		int iModelIndex = g_pGame->LoadModel(m_dwModelHash);

		// Save the local player index
		unsigned int uiLocalPlayerIndex = CPools::GetLocalPlayerIndex();

		// Set the local player index to the new player
		//CPools::SetLocalPlayerIndex(m_uiPlayerIndex);

		// Create the player ped
		DWORD dwFunc = (g_pClient->GetBaseAddress() + 0x81CB90);
		unsigned int uPlayerIndex = m_uiPlayerIndex;
		WORD wPlayerData = MAKEWORD(0, 1);
		WORD * pPlayerData = &wPlayerData;
		IVPed * pPlayerPed = NULL;
		_asm
		{
			push 0
			push iModelIndex
			push uPlayerIndex
			push pPlayerData
			call dwFunc
			add esp, 10h
			mov pPlayerPed, eax
		}

		// Restore the local player index
		CPools::SetLocalPlayerIndex(uiLocalPlayerIndex);

		if(pPlayerPed)
		{
			// Not too sure what this does
			dwFunc = (g_pClient->GetBaseAddress() + 0x89EC20);
			_asm
			{
				push 2
				mov ecx, pPlayerPed
				call dwFunc
			}

			// Create the player ped instance
			// TODO: Use GetPlayerPedFromIndex on m_uiPlayerIndex?
			m_pPlayerPed = new CIVPlayerPed(CPools::GetPlayerPedFromPed(pPlayerPed));

			// Add the player ped to the world
			m_pPlayerPed->AddToWorld();

			// Testing code
			unsigned int uiCharHandle;
			InvokeNative<void *>(0x511454A9, m_uiPlayerIndex, &uiCharHandle); // GET_PLAYER_CHAR
			InvokeNative<void *>(0x689D0F5F, uiCharHandle, -341.36f, 1144.80f, 14.79f); // SET_CHAR_COORDINATES
			InvokeNative<void *>(0x46B5523B, uiCharHandle, 40.114815f); // SET_CHAR_HEADING
		}
#endif
		int iModelIndex = g_pGame->LoadModel(m_dwModelHash);

		// Invalid model
		if(iModelIndex == -1)
			return false;

		/*LOBYTE(PlayerData) = GetLocalPlayerPed;
		BYTE1(PlayerData) = 1;*/
		WORD wPlayerData = MAKEWORD(0, 1);

		typedef CIVPed * (__cdecl * CreatePlayer__Internal_t)(WORD * ptr, int iIndex, int ModelIndex, int Unknown001); // done
		CreatePlayer__Internal_t pCreatePlayer__Internal = (CreatePlayer__Internal_t)(g_pClient->GetBaseAddress() + 0x81CB90); // done

		// Save the local player index
		unsigned int uiLocalPlayerIndex = CPools::GetLocalPlayerIndex();

		CIVPed * pPlayerPed = pCreatePlayer__Internal(&wPlayerData, m_uiPlayerIndex, iModelIndex, 0); // done

		// Restore the local player index
		CPools::SetLocalPlayerIndex(uiLocalPlayerIndex);

		typedef char (__thiscall * sub_89EE30_t)(CIVPed * pThis, char a2); // done
		sub_89EE30_t psub_89EE30 = (sub_89EE30_t)(g_pClient->GetBaseAddress() + 0x89EC20); // done
		psub_89EE30(pPlayerPed, 2); // done

		CIVWorld::Add((IVEntity *)pPlayerPed);

		//typedef int (__fastcall * sub_A48700_t)(int a1);
		//sub_A48700_t psub_A48700 = (sub_A48700_t)(g_pClient->GetBaseAddress() + 0xA48700);
		//psub_A48700(ReturnPtr);

		typedef int (__cdecl * sub_832AF0_t)(int a1, int a2); // done
		sub_832AF0_t psub_832AF0 = (sub_832AF0_t)(g_pClient->GetBaseAddress() + 0x832AF0); // done
		psub_832AF0(iModelIndex, g_pGame->GetResourceTypeIndex(RESOURCE_TYPE_WDR)); // done

		// Task Assignment
		int _v16 = *(DWORD *)(pPlayerPed->GetPed()->m_pPedIntelligence); // done
		int _v17 = (*(int (**)(void))(**(DWORD **)(pPlayerPed + 0xA90) + 0x1C))(); // done
		typedef void (__thiscall * sub_9E58B0_t)(int pthis, int a2, int a3, int a4); // done
		sub_9E58B0_t psub_9E58B0 = (sub_9E58B0_t)(g_pClient->GetBaseAddress() + 0x9E58B0); // done
		psub_9E58B0((_v16 + 0x44), _v17, 4, 0); // done // ped intelligence + 0x44 = task manager // CPedTaskManager::AssignTask
		//

		int (__thiscall * v17)(CIVPed *, DWORD, DWORD); // done
		v17 = *(int (__thiscall **)(CIVPed *, DWORD, DWORD))(*(DWORD *)pPlayerPed + 0xF4); // done
		v17(pPlayerPed, 200, 0); // done // param 2 used to be 0

		m_pPlayerPed = new CIVPlayerPed(CPools::GetPlayerPedFromIndex(m_uiPlayerIndex));

		// Testing code
		unsigned int uiCharHandle;
		InvokeNative<void *>(0x511454A9, m_uiPlayerIndex, &uiCharHandle); // GET_PLAYER_CHAR
		// TODO: SET_CHAR_HEALTH
		InvokeNative<void *>(0x689D0F5F, uiCharHandle, -341.36f, 1144.80f, 14.79f); // SET_CHAR_COORDINATES
		InvokeNative<void *>(0x46B5523B, uiCharHandle, 40.114815f); // SET_CHAR_HEADING
	}

	// Already created
	return false;
}

void CPlayer::Destroy()
{
	// Are we spawned?
	if(IsSpawned())
	{
		CLogFile::Printf("CPlayer::Destroy 1");
		// Remove the ped from the world
		m_pPlayerPed->RemoveFromWorld();
		CLogFile::Printf("CPlayer::Destroy 2");

		// Delete the player ped
		DWORD dwFunc = (g_pClient->GetBaseAddress() + 0x9C2260); // CPlayerPed::~CPlayerPed
		CLogFile::Printf("CPlayer::Destroy 3");
		IVPed * pPlayerPed = m_pPlayerPed->GetPed();
		CLogFile::Printf("CPlayer::Destroy 4");
		_asm
		{
			push 1
			mov ecx, pPlayerPed
			call dwFunc
		}
		CLogFile::Printf("CPlayer::Destroy 5");

		// Delete the players ped
		InvokeNative<void *>(0x0E3B49BF, CPools::GetHandleFromPed(pPlayerPed)); // DELETE_CHAR

		CLogFile::Printf("CPlayer::Destroy 6666");

		// Set the player ped pointer in the array to NULL
		CPools::SetPlayerPedAtIndex(m_uiPlayerIndex, NULL);
		CLogFile::Printf("CPlayer::Destroy 6");

		// Delete the player ped
		//InvokeNative<void *>(0x627A3586, m_uiPlayerIndex); // DELETE_PLAYER
		/*DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_DeletePlayer);
		unsigned int uiPlayerIndex = m_uiPlayerIndex;
		_asm
		{
			push uiPlayerIndex
			call dwFunc
			add esp, 4
		}*/

		// Delete the player ped instance
		delete m_pPlayerPed;
		CLogFile::Printf("CPlayer::Destroy 7");

		// Set the player ped instance to NULL
		m_pPlayerPed = NULL;
		CLogFile::Printf("CPlayer::Destroy 8");
	}
}

bool CPlayer::SetModelByHash(DWORD dwModelHash)
{
	// Get the model index from the hash
	int iModelIndex = g_pGame->GetModelIndexByHash(dwModelHash);

	// Is the model index valid?
	if(iModelIndex != -1)
	{
		// Set the model hash
		m_dwModelHash = dwModelHash;

		// TODO: Set the player model
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

bool CPlayer::SetPosition(Vector3 * vecPosition)
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
