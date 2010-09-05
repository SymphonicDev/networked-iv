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
	SetEntity((IVEntity *)pPlayerPed->m_pPed);
}

IVPlayerPed * CIVPlayerPed::GetPlayerPed()
{
	return m_pPlayerPed;
}

void CIVPlayerPed::SetName(char * szName)
{
	if(m_pPlayerPed)
		strncpy(m_pPlayerPed->m_szName, szName, sizeof(szName));
}

char * CIVPlayerPed::GetName()
{
	if(m_pPlayerPed)
		return m_pPlayerPed->m_szName;

	return 0;
}

void CIVPlayerPed::SetColour(DWORD dwColour)
{
	if(m_pPlayerPed)
		m_pPlayerPed->m_dwColour = dwColour;
}

DWORD CIVPlayerPed::GetColour()
{
	if(m_pPlayerPed)
		m_pPlayerPed->m_dwColour;

	return 0;
}

void CIVPlayerPed::SetPed(IVPed * pPed)
{
	if(m_pPlayerPed)
	{
		m_pPlayerPed->m_pPed = pPed;
		SetEntity((IVEntity *)pPed);
	}
}

IVPed * CIVPlayerPed::GetPed()
{
	if(m_pPlayerPed)
		return m_pPlayerPed->m_pPed;

	return NULL;
}
