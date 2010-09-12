//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVPlayerInfo.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

struct IVPlayerInfo
{
	PAD(pad0, 0x4C);						 // 000-04C
	char m_szName[20];  					 // 04C-060
	PAD(pad1, 0x434);						 // 060-494
	DWORD m_dwLastHitPedTime;				 // 494-498
	DWORD m_dwLastHitBuildingTime;			 // 498-49C
	DWORD m_dwLastHitObjectTime;			 // 49C-4A0
	DWORD m_dwLastDroveOnPavementTime;		 // 4A0-4A4
	DWORD m_dwLastRanLightTime;				 // 4A4-4A8
	DWORD m_dwLastDroveAgainstTrafficTime;   // 4A8-4AC
	PAD(pad2, 0x2E);						 // 4AC-4DA
	BYTE m_bytePlayerNumber;				 // 4DA-4DB
	PAD(pad3, 0x1);							 // 4DB-4DC
	DWORD m_dwState;						 // 4DC-4E0 - 3: dead
	PAD(pad4, 0x66);						 // 4E0-546
	BYTE m_byteNeverGetsTired;				 // 546-547
	BYTE m_byteFastReload;					 // 547-548
	BYTE m_byteFireProof;					 // 548-549
	PAD(pad6, 0x1);							 // 549-54A
	WORD m_wMaxHealth;						 // 54A-54C
	WORD m_wMaxArmour;						 // 54C-54E
	PAD(pad7, 0x1);							 // 54E-54F // Doesn't lose money after jail/arrest?
	BYTE m_byteFreeHealthCareset;			 // 54F-550
	BYTE m_byteCanDoDriveBy;				 // 550-551
	BYTE m_byteCanBeHassledByGangs;			 // 551-552
	PAD(pad8, 0x2);							 // 552-554
	DWORD dwFlags1;							 // 554-558 - Bits 0: can use cover, 2: damaged at least one ped, 3: damaged at least one vehicle
	PAD(pad9, 0x4);							 // 558-55C
	DWORD m_dwPlayerMood;					 // 55C-560
	PAD(pad10, 0x10);						 // 560-570
	DWORD m_dwColour;						 // 570-574
	DWORD m_dwTeam;							 // 574-578
	PAD(pad11, 0x8);						 // 578-580
	BYTE m_byteNetworkHasDiedRecently;		 // 580-581
	PAD(pad12, 0xB);						 // 581-58C
	IVPlayerPed * m_pPlayerPed;				 // 58C-590
	PAD(pad13, 0x4);						 // 590-594
	IVVehicle * m_pMayOnlyEnterThisVehicle;  // 594-598
};

class CIVPlayerInfo
{
private:
	IVPlayerInfo * m_pPlayerInfo;

public:
	CIVPlayerInfo();
	CIVPlayerInfo(IVPlayerInfo * pPlayerInfo);
	~CIVPlayerInfo();

	void           SetPlayerInfo(IVPlayerInfo * pPlayerInfo);
	IVPlayerInfo * GetPlayerInfo();

	void           SetName(char * szName);
	char *         GetName();
	void           SetColour(DWORD dwColour);
	DWORD          GetColour();
	void           SetPlayerPed(IVPlayerPed * pPlayerPed);
	IVPlayerPed *  GetPlayerPed();
};
