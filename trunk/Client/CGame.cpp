//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CGame.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//          Contains public domain code from xliveless by listener
//
//==========================================================================

#include <StdInc.h>

extern CClient *	 g_pClient;
extern CGame *		 g_pGame;
extern CChatWindow * g_pChatWindow;

CGame::CGame()
{
	// Determine the game version
	unsigned int * puiVersionTest = (unsigned int *)(g_pClient->GetBaseAddress() + 0x48C0E7);

	if(*puiVersionTest == 0x20245C89)
		m_gameVersion = GAME_VERSION_7;
	else
	{
		MessageBox(NULL, "Unknown game version detected. Networked: IV currently only supports version 1.0.7.0", "Unknown game version", NULL);
		ExitProcess(0);
	}
}

CGame::~CGame()
{

}

int iScriptLoadStage = 0;

int CScriptVM__Process()
{
	if(iScriptLoadStage == 0)
	{
		// Get the script thread pool
		CSimpleCollection<GtaThread> * pThreads = (CSimpleCollection<GtaThread> *)(g_pClient->GetBaseAddress() + VAR_ScrVM__ThreadPool_7);

		// Set the current script count and script thread pool size to 0
		pThreads->Size = 0;
		pThreads->Count = 0;

		// Create the local player
		unsigned int uiPlayerIndex;
		InvokeNative<void *>(0x335E3951, 0, 0.0f, 0.0f, 0.0f, &uiPlayerIndex); // CREATE_PLAYER

		// Get the local players char handle
		unsigned int uiCharHandle;
		InvokeNative<void *>(0x511454A9, uiPlayerIndex, &uiCharHandle); // GET_PLAYER_CHAR

		// Set the local players initial coordinates
		//InvokeNative<void *>(0x689D0F5F, uiCharHandle, 0.0f, 0.0f, 0.0f); // SET_CHAR_COORDINATES
		InvokeNative<void *>(0x689D0F5F, uiCharHandle, -341.36f, 1144.80f, 14.79f); // SET_CHAR_COORDINATES

		// Set the local players initial heading
		//InvokeNative<void *>(0x46B5523B, uiCharHandle, 0.0f); // SET_CHAR_HEADING
		InvokeNative<void *>(0x46B5523B, uiCharHandle, 40.114815f); // SET_CHAR_HEADING

		// Disable wanted level
		InvokeNative<void *>(0x5D622498, 0); // SET_MAX_WANTED_LEVEL

		iScriptLoadStage++;
	}

	if(iScriptLoadStage <= 2)
	{
		if(InvokeNative<bool>(0x59EE3A11) || InvokeNative<bool>(0x0A940E03)) // IS_SCREEN_FADED_OUT // IS_SCREEN_FADING_OUT
		{
			g_pGame->FadeScreen(FADE_TYPE_IN, 0);
			iScriptLoadStage++;
		}
	}

	if(iScriptLoadStage == 3)
	{
		//g_pGame->FadeScreen(FADE_TYPE_OUT, 0);
		g_pClient->OnGameLoad();
		iScriptLoadStage++;
	}

	return 1;
}

void _declspec(naked) CScriptVM__Process_Hook()
{
	// Usually this would loop through all running script threads
	// and call scrThread::Loop with opsToExecute set to (FORGOT THE VALUE)
	_asm
	{
		pushad
	}

	CScriptVM__Process();

	_asm
	{
		popad
		mov al, 1
		retn
	}
}

void _declspec(naked) StartGame_Hook()
{
	_asm
	{
		pushad
		int 3
		popad
	}
}

void _declspec(naked) EFLCSelect_Hook()
{
	_asm
	{
		pushad
		int 3
		popad
	}
}

void CGame::ApplyPatches()
{
	if(m_gameVersion == GAME_VERSION_7)
	{
		// Unprotect the .text segment
		CPatcher::Unprotect((g_pClient->GetBaseAddress() + 0x400000 + 0x1000), 0x94C000);

		// Unprotect the .rdata segment
		CPatcher::Unprotect((g_pClient->GetBaseAddress() + 0x400000 + 0x94D000), 0x1BF000);

		// test start game func hook
		//CPatcher::InstallJmpPatch((g_pClient->GetBaseAddress() + 0x7B9980), (DWORD)StartGame_Hook);

		// test eflc selector hook
		// 0x858C70 - tlad/tbogt screen loader
		// 0x858C70 - eflc selector input handler (vanilla/iv screen and tlad/tbogt screen) handler
		// 0x859E60 - load tlad menu (episode 1)
		// 0x859E25 - load vanilla menu (episode 0)
		// 0x8589D3 - load vanilla/iv screen
		// 0x41FD90 - CGame::StartGame
		//CPatcher::InstallJmpPatch((g_pClient->GetBaseAddress() + 0x8589D3), (g_pClient->GetBaseAddress() + 0x859E25));

		// Hook for CScriptVM::Process
		CPatcher::InstallCallPatch((g_pClient->GetBaseAddress() + 0x80A092), (DWORD)CScriptVM__Process_Hook, 5);

		// Disable legal screens
		//*(BYTE *)(g_pClient->GetBaseAddress() + 0x422CCC) = 0xEB;
		//*(BYTE *)(g_pClient->GetBaseAddress() + 0x422CCD) = 0x3E;

		// Disable r* and gta intro screens
		// TODO

		// Don't load startup.sco
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x809A81) = 0xEB;
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x809A82) = 0x61;

		// Always start a new game
		// TODO: Change, this is messy
		CPatcher::InstallJmpPatch((g_pClient->GetBaseAddress() + 0x5B0311), (g_pClient->GetBaseAddress() + 0x5B03BF));

		// Stop game pausing
		// TODO

		// NOTE: All the functions below are all called from 0x4212A0 in one way or another
		// so find out what 0x4212A0 does

		// Disable parked cars
		CPatcher::InstallRetnPatch(g_pClient->GetBaseAddress() + 0xB3EDF0);

		// Disable emergency services and garbage trucks
		CPatcher::InstallNopPatch((g_pClient->GetBaseAddress() + 0x4215CF), 5);

		// Disable random peds and vehicles
		CPatcher::InstallNopPatch((g_pClient->GetBaseAddress() + 0x8ACD64), 5);

		// Disable scenario peds
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x9F72C0) = 0xB8; // mov eax,
		*(DWORD *)(g_pClient->GetBaseAddress() + 0x9F72C1) = 0x0; // 0
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x9F72C5) = 0xC3; // retn

		// Stop creation of certain entitys from non scripting threads causing a crash
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x9E6BD0) = 0xB0;   // mov al,
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x9E6BD1) = 0x00;   // 0
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x9E6BD2) = 0xC2;   // retn
		*(WORD *)(g_pClient->GetBaseAddress() + 0x9E6BD3) = 0x0004; // 4

		// Shorten the initial sleep time
		*(DWORD *)(g_pClient->GetBaseAddress() + 0x401835) = 1;

		// Disable error reporting
		CPatcher::InstallRetnPatch((g_pClient->GetBaseAddress() + 0xD356D0));

		// Certificates check
		*(DWORD *)(g_pClient->GetBaseAddress() + 0x403F10) = 0x900008C2;

		// 
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x40262D) = 0x33; // xor eax
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x40262E) = 0xC0; // eax
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x40262F) = 0xE9; // jmp
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x402630) = 0x4A; // +4Ah

		// Skip RGSC connect and EFC checks (jmp 40289E)
		*(DWORD *)(g_pClient->GetBaseAddress() + 0x402631) = 0x90000002;

		// NOP; MOV [g_rgsc], eax
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x402883) = 0x90;
		*(BYTE *)(g_pClient->GetBaseAddress() + 0x402884) = 0xA3;

		// Disable VDS101 error
		// TODO

		// Disable VDS102 error
		CPatcher::InstallNopPatch((g_pClient->GetBaseAddress() + 0x4028ED), 42);

		// Last RGSC init check
		CPatcher::InstallNopPatch((g_pClient->GetBaseAddress() + 0x40291D), 6);

		// 
		CPatcher::InstallNopPatch((g_pClient->GetBaseAddress() + 0x402B12), 14);
		CPatcher::InstallNopPatch((g_pClient->GetBaseAddress() + 0x402D17), 14);

		// 
		*(DWORD *)(g_pClient->GetBaseAddress() + 0x403870) = 0x90CC033; // xor eax, eax; retn
		*(DWORD *)(g_pClient->GetBaseAddress() + 0x404250) = 0x90CC033; // xor eax, eax; retn

		// Disable securom spot checks (mov al, 1; retn; nop)
		*(DWORD *)(g_pClient->GetBaseAddress() + 0xBAC160) = 0x90C301B0;
		*(DWORD *)(g_pClient->GetBaseAddress() + 0xBAC180) = 0x90C301B0;
		*(DWORD *)(g_pClient->GetBaseAddress() + 0xBAC190) = 0x90C301B0;
		*(DWORD *)(g_pClient->GetBaseAddress() + 0xBAC1C0) = 0x90C301B0;
	}
}

unsigned int CGame::GetResourceTypeIndex(eResourceType resourceType)
{
	switch(resourceType)
	{
	case RESOURCE_TYPE_WDR:
		return *(unsigned int *)(g_pClient->GetBaseAddress() + VAR_FileTypeWdrIndex_7);
	}

	return 0;
}

int CGame::GetModelIndexByHash(DWORD dwModelHash)
{
	DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_GetModelByHash_7);
	int iModelIndex = -1;
	int * pModelIndex = &iModelIndex;
	_asm
	{
		push pModelIndex
		push dwModelHash
		call dwFunc
		add esp, 8
	}
	return iModelIndex;
}

int CGame::RequestModel(DWORD dwModelHash)
{
	int iModelIndex = GetModelIndexByHash(dwModelHash);

	if(iModelIndex != -1)
	{
		DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_RequestResource_7);
		unsigned int uFileTypeIndex = GetResourceTypeIndex(RESOURCE_TYPE_WDR);
		_asm
		{
			push 1Ah
			push uFileTypeIndex
			push iModelIndex
			call dwFunc
			add esp, 0Ch
		}
		// TODO: Do something with return value?
	}

	return iModelIndex;
}

void CGame::LoadRequestedModels()
{
	DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_LoadRequestedResources_7);
	_asm
	{
		push 1
		call dwFunc
		add esp, 4
	}
}

bool CGame::HasModelLoaded(DWORD dwModelHash)
{
	int iModelHash = GetModelIndexByHash(dwModelHash);

	if(iModelHash != -1)
	{
		DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_HasResourceLoaded_7);
		unsigned int uFileTypeIndex = GetResourceTypeIndex(RESOURCE_TYPE_WDR);
		bool bLoaded = false;
		_asm
		{
			push uFileTypeIndex
			push iModelHash
			call dwFunc
			add esp, 8
			mov bLoaded, al
		}
		return bLoaded;
	}

	return false;
}

void CGame::UnloadModel(DWORD dwModelHash)
{
	// TODO
}

int CGame::LoadModel(DWORD dwModelHash)
{
	if(!HasModelLoaded(dwModelHash))
	{
		int iModelIndex = RequestModel(dwModelHash);
		LoadRequestedModels();

		while(!HasModelLoaded(dwModelHash))
			Sleep(5);

		return iModelIndex;
	}

	return GetModelIndexByHash(dwModelHash);
}

// TODO: CIVVehicleFactory
DWORD CGame::CreateVehicle(DWORD dwModelHash)
{
	unsigned int uiVehicleHandle;
	InvokeNative<void *>(0x2F1D6843, dwModelHash, -346.36f, 1144.80f, 14.79f, &uiVehicleHandle, true);
	return NULL;
	/*DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CVehicleFactory__Create_7);
	DWORD dwVehicleFactory = (g_pClient->GetBaseAddress() + VAR_VehicleFactory_7);
	int iUnknown = 0;
	int iModelIndex = LoadModel(dwModelHash);
	DWORD dwVehicle = NULL;
	_asm
	{
		push 1 ; somthing to do with physics
		push iUnknown ; unknown
		push 2 ; unknown
		push iModelIndex
		mov ecx, dwVehicleFactory
		call dwFunc
		mov dwVehicle, eax
	}*/
	//return dwVehicle;
}

// TODO: CIVVehicleFactory
void CGame::DeleteVehicle(DWORD dwVehicle)
{
	DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CVehicleFactory__Delete_7);
	DWORD dwVehicleFactory = (g_pClient->GetBaseAddress() + VAR_VehicleFactory_7);
	_asm
	{
		push dwVehicle
		mov ecx, dwVehicleFactory
		call dwFunc
	}
}

// NOTE: Find out if the time is unsigned
// TODO: Some sort of 'show loading...' option
void CGame::FadeScreen(eFadeType fadeType, int iTime)
{
	if(fadeType == FADE_TYPE_IN_UNHACKED)
		InvokeNative<void *>(0x5F9218C3, iTime); // DO_SCREEN_FADE_IN_UNHACKED
	else if(fadeType == FADE_TYPE_IN)
		InvokeNative<void *>(0x4D72200, iTime); // DO_SCREEN_FADE_IN
	else if(fadeType == FADE_TYPE_OUT_UNHACKED)
		InvokeNative<void *>(0x42D250A7, iTime); // DO_SCREEN_FADE_OUT_UNHACKED
	else if(fadeType == FADE_TYPE_OUT)
		InvokeNative<void *>(0x65DE621C, iTime); // DO_SCREEN_FADE_OUT
}
