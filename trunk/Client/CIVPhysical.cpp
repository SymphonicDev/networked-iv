//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVPhysical.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

extern CClient * g_pClient;

CIVPhysical::CIVPhysical()
{

}

CIVPhysical::~CIVPhysical()
{

}

IVPhysical * CIVPhysical::GetPhysical()
{
	return (IVPhysical *)GetEntity();
}

void CIVPhysical::SetMoveSpeed(Vector3 * vecMoveSpeed)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
	{
		DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CPhysical__SetMoveSpeed_7);
		_asm
		{
			push vecMoveSpeed
			mov ecx, pPhysical
			call dwFunc
		}
	}
}

void CIVPhysical::GetMoveSpeed(Vector3 * vecMoveSpeed)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
	{
		DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CPhysical__GetMoveSpeed_7);
		_asm
		{
			push vecMoveSpeed
			mov ecx, pPhysical
			call dwFunc
		}
	}
}

void CIVPhysical::SetTurnSpeed(Vector3 * vecTurnSpeed)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
	{
		DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CPhysical__SetTurnSpeed_7);
		_asm
		{
			push vecTurnSpeed
			mov ecx, pPhysical
			call dwFunc
		}
	}
}

void CIVPhysical::GetTurnSpeed(Vector3 * vecTurnSpeed)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();
	
	if(pPhysical)
	{
		DWORD dwFunc = (g_pClient->GetBaseAddress() + FUNC_CPhysical__GetTurnSpeed_7);
		_asm
		{
			push vecTurnSpeed
			mov ecx, pPhysical
			call dwFunc
		}
	}
}

void CIVPhysical::SetLastDamageEntity(IVEntity * pLastDamageEntity)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
		pPhysical->m_pLastDamageEntity = pLastDamageEntity;
}

IVEntity * CIVPhysical::GetLastDamageEntity()
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
		return pPhysical->m_pLastDamageEntity;

	return NULL;
}
