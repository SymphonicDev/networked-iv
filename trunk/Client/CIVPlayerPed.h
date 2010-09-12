//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVPlayerPed.h
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

struct IVPlayerPed
{
	IVPed m_ped;
};

class CIVPlayerPed : public CIVPed
{
private:
	IVPlayerPed * m_pPlayerPed;

public:
	CIVPlayerPed();
	CIVPlayerPed(IVPlayerPed * pPlayerPed);
	~CIVPlayerPed();

	void          SetPlayerPed(IVPlayerPed * pPlayerPed);
	IVPlayerPed * GetPlayerPed();
};
