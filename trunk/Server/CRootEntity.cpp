//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CRootEntity.cpp
// Project: Server
// Author(s): mabako
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CRootEntity::CRootEntity() : CEntity(CEntity::ROOT, NULL, "root")
{
}

CRootEntity::~CRootEntity()
{
}

bool CRootEntity::SetParent(CEntity* pEntity)
{
	return false;
}
