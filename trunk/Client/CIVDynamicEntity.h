//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVDynamicEntity.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

struct IVDynamicEntity
{
	IVEntity m_entity; // 000-074
	PAD(pad0, 0x4);	   // 074-078
	DWORD m_pAnim;	   // 078-07C
	PAD(pad1, 0x90);   // 07C-10C
};

class CIVDynamicEntity : public CIVEntity
{
public:
	CIVDynamicEntity();
	~CIVDynamicEntity();

	IVDynamicEntity * GetDynamicEntity();
};
