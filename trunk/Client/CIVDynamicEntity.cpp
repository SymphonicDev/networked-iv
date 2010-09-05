//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CIVDynamicEntity.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CIVDynamicEntity::CIVDynamicEntity()
{

}

CIVDynamicEntity::~CIVDynamicEntity()
{

}

IVDynamicEntity * CIVDynamicEntity::GetDynamicEntity()
{
	return (IVDynamicEntity *)GetEntity();
}
