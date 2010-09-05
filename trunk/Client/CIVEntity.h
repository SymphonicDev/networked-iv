//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVEntity.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

#define FUNC_CEntity__IsTouchingEntity_7 0xA47B30

struct IVEntity
{
	DWORD m_dwVFTable;		   // 00-04
	PAD(pad0, 0xC);			   // 04-10
	Vector3 m_vecPosition;	   // 10-1C
	float m_fHeading;		   // 1C-20
	Matrix34 * m_pMatrix;	   // 20-24
	DWORD m_dwFlags1;		   // 24-28 - Bits 0: has collision model, 3: don't load collisions, 5: is visible, 12: draw last
	DWORD m_dwFlags2;		   // 28-2C - Bits 2: lights, 21: on fire
	WORD m_w2C;				   // 2C-2E
	WORD m_wModelIndex;		   // 2E-30
	IVEntity * m_pReferences;  // 30-34
	DWORD m_pLivery;		   // 34-38 - Not sure about this, all i know is ((ent + 0x34) + 0xD8) = vehicle livery
	DWORD m_pColModel;		   // 38-3C
	PAD(pad3, 0xC);			   // 3C-48
	DWORD m_hInterior;		   // 48-4C
	PAD(pad4, 0x17);		   // 4C-63
	BYTE m_byteAlpha;		   // 63-64
	PAD(pad5, 0x10);		   // 64-74
};

class CIVEntity
{
private:
	IVEntity * m_pEntity;

public:
	CIVEntity();
	~CIVEntity();

	void       SetEntity(IVEntity * pEntity);
	IVEntity * GetEntity();

	void       SetMatrix(Matrix34 * matMatrix);
	void       GetMatrix(Matrix34 * matMatrix);
	void       SetPosition(Vector3 * vecPosition);
	void       GetPosition(Vector3 * vecPosition);
	void       SetRoll(Vector3 * vecRoll);
	void       GetRoll(Vector3 * vecRoll);
	void       SetDirection(Vector3 * vecDirection);
	void       GetDirection(Vector3 * vecDirection);
	WORD       GetModelIndex();
	void       SetAlpha(BYTE byteAlpha);
	BYTE       GetAlpha();
	bool       IsTouchingEntity(IVEntity * pTouchingEntity);
	void       AddToWorld();
	void       RemoveFromWorld();
};
