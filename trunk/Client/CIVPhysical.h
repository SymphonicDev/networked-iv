//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVPhysical.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

#define FUNC_CPhysical__SetMoveSpeed_7 0xA47750
#define FUNC_CPhysical__GetMoveSpeed_7 0xA477F0
#define FUNC_CPhysical__SetTurnSpeed_7 0xA47840
#define FUNC_CPhysical__GetTurnSpeed_7 0xA478E0

struct IVPhysical
{
	IVDynamicEntity m_dynamicEntity; // 000-10C
	// 13C - In Water (BYTE)?
	PAD(pad0, 0xD8);				 // 10C-1E4
	IVEntity * m_pLastDamageEntity; // 1E4-1E8
	PAD(pad1, 0xC);					 // 1E8-1F4
	PAD(pad2, 0x1C);				 // 1F4-210
};

class CIVPhysical : public CIVDynamicEntity
{
public:
	CIVPhysical();
	~CIVPhysical();

	IVPhysical * GetPhysical();

	void         SetMoveSpeed(Vector3 * vecMoveSpeed);
	void         GetMoveSpeed(Vector3 * vecMoveSpeed);
	void         SetTurnSpeed(Vector3 * vecTurnSpeed);
	void         GetTurnSpeed(Vector3 * vecTurnSpeed);
	void         SetLastDamageEntity(IVEntity * pLastDamageEntity);
	IVEntity *  GetLastDamageEntity();
};
