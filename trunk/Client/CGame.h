//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CGame.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

#define FUNC_GetModelByHash_7 0x98AAE0
#define FUNC_RequestResource_7 0x832C40
#define VAR_FileTypeWdrIndex_7 0x15F73A0
#define FUNC_LoadRequestedResources_7 0x832C20
#define FUNC_HasResourceLoaded_7 0x832DD0
#define VAR_VehicleFactory_7 0x15F5514
#define FUNC_CVehicleFactory__Create_7 0x443D60
#define FUNC_CVehicleFactory__Delete_7 0x973AA0

enum eGameVersion
{
	GAME_VERSION_7
};

enum eResourceType
{
	RESOURCE_TYPE_WDR
};

enum eFadeType
{
	FADE_TYPE_IN_UNHACKED,
	FADE_TYPE_IN,
	FADE_TYPE_OUT_UNHACKED,
	FADE_TYPE_OUT
};

class CGame
{
private:
	eGameVersion m_gameVersion;

public:
	CGame();
	~CGame();

	void         ApplyPatches();
	unsigned int GetResourceTypeIndex(eResourceType fileType);
	int          GetModelIndexByHash(DWORD dwModelHash);
	int          RequestModel(DWORD dwModelHash);
	void         LoadRequestedModels();
	bool         HasModelLoaded(DWORD dwModelHash);
	void         UnloadModel(DWORD dwModelHash);
	int          LoadModel(DWORD dwModelHash);
	DWORD        CreateVehicle(DWORD dwModelHash, Vector3 * vecPosition);
	void         DeleteVehicle(DWORD dwVehicle);
	void         FadeScreen(eFadeType fadeType, int iTime);
};
