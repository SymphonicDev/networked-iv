//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVPed.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

#define IVVehicle void

enum ePedType
{
	PED_TYPE_PLAYER,
	PED_TYPE_CIVMALE,
	PED_TYPE_CIVFEMALE,
	PED_TYPE_COP,
	PED_TYPE_GANG_ALBANIAN,
	PED_TYPE_GANG_BIKER_1,
	PED_TYPE_GANG_BIKER_2,
	PED_TYPE_GANG_ITALIAN,
	PED_TYPE_GANG_RUSSIAN,
	PED_TYPE_GANG_RUSSIAN_2,
	PED_TYPE_GANG_IRISH,
	PED_TYPE_GANG_JAMAICAN,
	PED_TYPE_GANG_AFRICAN_AMERICAN,
	PED_TYPE_GANG_KOREAN,
	PED_TYPE_GANG_CHINESE_JAPANESE,
	PED_TYPE_GANG_PUERTO_RICAN,
	PED_TYPE_DEALER,
	PED_TYPE_MEDIC,
	PED_TYPE_FIREMAN,
	PED_TYPE_CRIMINAL,
	PED_TYPE_BUM,
	PED_TYPE_PROSTITUTE,
	PED_TYPE_SPECIAL//,
	//PED_TYPE_MISSION(1-8),
	//PED_TYPE_NETWORK_PLAYER_(1-32),
	//PED_TYPE_NETWORK_TEAM_(1-8)
};

struct IVPedIntelligence
{
	PAD(pad0, 0x44);
	DWORD m_pPedTaskManager;
	// TODO: Find size
};

struct IVPedWeapon
{
	PAD(pad0, 0xC);
};

struct IVPedWeapons
{
	PAD(pad0, 0x3C);           // 000-03C
	IVPedWeapon m_weapons[10]; // 03C-0B4
	PAD(pad1, 0x64);           // 0B4-118
	BYTE m_byteCurrentWeapon;  // 118-119
	PAD(pad2, 0x1);            // 119-11A
};

struct IVPed
{
	IVPhysical m_physical;					// 000-210
	PAD(pad0, 0xC);							// 210-21C
	DWORD m_pPedBase;						// 21C-220
	PAD(pad1, 0x4);							// 220-224
	IVPedIntelligence * m_pPedIntelligence;	// 224-228
	PAD(pad2, 0x4);							// 228-22C // CPlayerInfo pointer?
	PAD(pad3, 0x40);						// 22C-26C
	BYTE m_byteUnknown;						// 26C-26D - Bits 4: in vehicle
	PAD(pad4, 0x43);                        // 26D-2B0
	IVPedWeapons m_weapons;                 // 2B0-3CA
	// A70 - Ped Type (BYTE)
	PAD(pad6, 0x776);						// 3CA-B40
	IVVehicle * m_pCurrentVehicle;			// B40-B44
	PAD(pad7, 0x3BC);						// B44-F00
};

class CIVPed : public CIVPhysical
{
public:
	CIVPed();
	~CIVPed();

	IVPed *      GetPed();

	void         SetType(ePedType type);
	ePedType     GetType();
	bool         IsInVehicle();
	void         SetCurrentVehicle(IVVehicle * pVehicle);
	IVVehicle *  GetCurrentVehicle();
};
