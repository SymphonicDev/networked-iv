//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVPed.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CIVPed::CIVPed()
{

}

CIVPed::~CIVPed()
{

}

IVPed * CIVPed::GetPed()
{
	return (IVPed *)GetEntity();
}

void CIVPed::SetType(ePedType type)
{
	IVPed * pPed = (IVPed *)GetPed();

	if(pPed)
		*(ePedType *)(pPed->m_pPedBase + 0x12C) = type;
}

ePedType CIVPed::GetType()
{
	IVPed * pPed = (IVPed *)GetPed();

	if(pPed)
		return *(ePedType *)(pPed->m_pPedBase + 0x12C);

	return (ePedType)0;
}

bool CIVPed::IsInVehicle()
{
	IVPed * pPed = (IVPed *)GetPed();

	if(pPed)
		return ((pPed->m_byteUnknown & 4) != 0);

	return false;
}

void CIVPed::SetCurrentVehicle(IVVehicle * pVehicle)
{
	IVPed * pPed = (IVPed *)GetPed();

	if(pPed)
		pPed->m_pCurrentVehicle = pVehicle;
}

IVVehicle * CIVPed::GetCurrentVehicle()
{
	IVPed * pPed = (IVPed *)GetPed();

	if(pPed)
		return pPed->m_pCurrentVehicle;

	return NULL;
}
