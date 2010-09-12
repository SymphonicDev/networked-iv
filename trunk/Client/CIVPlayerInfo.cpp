//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVPlayerInfo.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CIVPlayerInfo::CIVPlayerInfo()
{
	m_pPlayerInfo = NULL;
}

CIVPlayerInfo::CIVPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	SetPlayerInfo(pPlayerInfo);
}

CIVPlayerInfo::~CIVPlayerInfo()
{

}

void CIVPlayerInfo::SetPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	m_pPlayerInfo = pPlayerInfo;
}

IVPlayerInfo * CIVPlayerInfo::GetPlayerInfo()
{
	return m_pPlayerInfo;
}

void CIVPlayerInfo::SetName(char * szName)
{
	if(m_pPlayerInfo)
		strncpy(m_pPlayerInfo->m_szName, szName, 20);
}

char * CIVPlayerInfo::GetName()
{
	if(m_pPlayerInfo)
		return m_pPlayerInfo->m_szName;

	return 0;
}

void CIVPlayerInfo::SetColour(DWORD dwColour)
{
	if(m_pPlayerInfo)
		m_pPlayerInfo->m_dwColour = dwColour;
}

DWORD CIVPlayerInfo::GetColour()
{
	if(m_pPlayerInfo)
		m_pPlayerInfo->m_dwColour;

	return 0;
}

void CIVPlayerInfo::SetPlayerPed(IVPlayerPed * pPlayerPed)
{
	if(m_pPlayerInfo)
		m_pPlayerInfo->m_pPlayerPed = pPlayerPed;
}

IVPlayerPed * CIVPlayerInfo::GetPlayerPed()
{
	if(m_pPlayerInfo)
		return m_pPlayerInfo->m_pPlayerPed;

	return NULL;
}
