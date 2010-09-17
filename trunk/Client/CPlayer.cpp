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
extern CGame *   g_pGame;

CPlayer::CPlayer(bool bLocalPlayer)
{
	if(bLocalPlayer)
	{
		// Set the player index to 0 (Local player)
		// TODO: Use the internal local player index here
		m_uiPlayerIndex = 0;

		// Create the player ped instance with the local player ped pointer
		m_pPlayerPed = new CIVPlayerPed(CPools::GetPlayerInfoFromIndex(0)->m_pPlayerPed);

		// Set the model hash to the default player model hash
		m_dwModelHash = MODEL_PLAYER;
	}
	else
	{
		// Find a free player ped index
		m_uiPlayerIndex = CPools::FindFreePlayerInfoIndex();

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
		// .text:0096D870 NewPlayerPed (P7)
		/*DWORD dwPedPool = (g_pClient->GetBaseAddress() + VAR_PedPool_7);
		DWORD dwFunc1 = (g_pClient->GetBaseAddress() + FUNC_CPool__Allocate_7);
		DWORD dwFunc2 = (g_pClient->GetBaseAddress() + 0x9C1910); // CPlayerPed::CPlayerPed
		DWORD dwPlayerPed = NULL;
		unsigned int uiPlayerIndex = m_uiPlayerIndex;
		_asm
		{
			mov ecx, dwPedPool
			call dwFunc1
			mov dwPlayerPed, eax
			push uiPlayerIndex
			push 0 ; might need to be 1
			push 1 ; if above is changed to 1 change to 0
			mov ecx, dwPlayerPed
			call dwFunc2
			add esp, 0Ch
		}*/
		CLogFile::Printf("Creation step 1");
		int iModelIndex = g_pGame->LoadModel(m_dwModelHash);

		CLogFile::Printf("Creation step 2");
		if(iModelIndex == -1)
		{
			// Invalid model hash
			return false;
		}

		// Save the local player index
		unsigned int uiLocalPlayerIndex = CPools::GetLocalPlayerIndex();
		CLogFile::Printf("Creation step 3");

		// Create player ped
		DWORD dwFunc = (g_pClient->GetBaseAddress() + 0x81CB90); // CreatePlayerPed
		WORD wPlayerData = MAKEWORD(0, 1);
		WORD * pwPlayerData = &wPlayerData;
		int iPlayerIndex = m_uiPlayerIndex;
		IVPlayerPed * pPlayerPed = NULL;
		CLogFile::Printf("Creation step 4");
		_asm
		{
			push 0 ; unknown 0
			push iModelIndex ; model index
			push iPlayerIndex ; player index
			push pwPlayerData ; unknown (0, 1) (word)
			call dwFunc
			mov pPlayerPed, eax
			add esp, 10h
		}
		CLogFile::Printf("Creation step 5");

		if(!pPlayerPed)
		{
			// Invalid player ped pointer
			return false;
		}

		// Restore the local player index
		CPools::SetLocalPlayerIndex(uiLocalPlayerIndex);
		CLogFile::Printf("Creation step 6");

		// Setup ped intelligence (?)
		dwFunc = (g_pClient->GetBaseAddress() + 0x89EC20); // SetupPedIntelligence
		_asm
		{
			push 2
			mov ecx, pPlayerPed
			call dwFunc
			add esp, 4
		}
		CLogFile::Printf("Creation step 7");

		// Add the player ped to the world (this should be a call to 0x817DF0 (P7))
		CIVWorld::Add((IVEntity *)pPlayerPed);
		CLogFile::Printf("Creation step 8");

		// Unknown
		dwFunc = (g_pClient->GetBaseAddress() + 0x832AF0);
		unsigned int uiResourceTypeWdrIndex = g_pGame->GetResourceTypeIndex(RESOURCE_TYPE_WDR);
		CLogFile::Printf("Creation step 9");
		_asm
		{
			push uiResourceTypeWdrIndex ; resource type index
			push iModelIndex ; model index
			call dwFunc
			add esp, 8
		}
		CLogFile::Printf("Creation step 10");

		// Create task
		/*int _v17 = (*(int (**)(void))(**(DWORD **)(pPlayerPed + 0xA90) + 0x1C))();
		CLogFile::Printf("Creation step 11");

		// Assign task to player ped
		dwFunc = (g_pClient->GetBaseAddress() + 0x9E58B0); // CPedTaskManager::AssignTask
		DWORD * dwTaskManager = pPlayerPed->m_ped.m_pPedIntelligence->m_pPedTaskManager;
		CLogFile::Printf("Creation step 12");
		_asm
		{
			push 0 ; unknown
			push 4 ; priority?
			push _v17 ; task pointer
			mov ecx, dwTaskManager
			call dwFunc
			add esp, 0Ch
		}*/
		CLogFile::Printf("Creation step 13");

		// Unknown
		dwFunc = (*(DWORD *)pPlayerPed + 0xF4);
		_asm
		{
			push 0
			push 200 ; used to be 0
			mov ecx, pPlayerPed
			call dwFunc
			add esp, 8
		}
		CLogFile::Printf("Creation step 14");

		m_pPlayerPed = new CIVPlayerPed(pPlayerPed);

		CLogFile::Printf("Creation step 15");

		// Testing code
		unsigned int uiCharHandle;
		InvokeNative<void *>(0x511454A9, m_uiPlayerIndex, &uiCharHandle); // GET_PLAYER_CHAR
		// TODO: SET_CHAR_HEALTH
		InvokeNative<void *>(0x689D0F5F, uiCharHandle, -341.36f, 1144.80f, 14.79f); // SET_CHAR_COORDINATES
		InvokeNative<void *>(0x46B5523B, uiCharHandle, 40.114815f); // SET_CHAR_HEADING
		CLogFile::Printf("Creation step 16");
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
		// Remove the player ped from the world
		m_pPlayerPed->RemoveFromWorld();
		CLogFile::Printf("CPlayer::Destroy 2");

		// Delete the player ped
		DWORD dwFunc = (g_pClient->GetBaseAddress() + 0x9C2260); // CPlayerPed::~CPlayerPed
		CLogFile::Printf("CPlayer::Destroy 3");
		IVPlayerPed * pPlayerPed = m_pPlayerPed->GetPlayerPed();
		CLogFile::Printf("CPlayer::Destroy 4");
		_asm
		{
			push 1
			mov ecx, pPlayerPed
			call dwFunc
			add esp, 4
		}
		CLogFile::Printf("CPlayer::Destroy 5");

		// need to remove the player ped from the pool too (i think player ped destructor does that for us)?

		// Delete the player ped instance
		delete m_pPlayerPed;
		CLogFile::Printf("CPlayer::Destroy 6");

		// Set the player ped instance to NULL
		m_pPlayerPed = NULL;
		CLogFile::Printf("CPlayer::Destroy 7");
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
