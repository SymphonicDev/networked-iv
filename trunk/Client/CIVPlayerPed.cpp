//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVPlayerPed.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CIVPlayerPed::CIVPlayerPed()
{
	m_pPlayerPed = NULL;
	SetPlayerPed(NULL);
}

CIVPlayerPed::CIVPlayerPed(IVPlayerPed * pPlayerPed)
{
	SetPlayerPed(pPlayerPed);
}

CIVPlayerPed::~CIVPlayerPed()
{

}

void CIVPlayerPed::SetPlayerPed(IVPlayerPed * pPlayerPed)
{
	m_pPlayerPed = pPlayerPed;
	SetEntity((IVEntity *)pPlayerPed);
}

IVPlayerPed * CIVPlayerPed::GetPlayerPed()
{
	return m_pPlayerPed;
}
