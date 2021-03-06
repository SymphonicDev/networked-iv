//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CTimer.h
// Project: Server
// Author(s): mabako
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

class CTimer : public CEntity
{
public:
			 CTimer(CResource* pResource, SQObjectPtr pFunction, unsigned long ulInterval, unsigned int uiAmountRepeating, CSquirrelArguments* pArguments);
			~CTimer();

	void	Reset();
	bool	Process(unsigned long ulTime);

	bool	SetParent(CEntity* pEntity);
private:
	SQObjectPtr			m_pFunction;
	unsigned long		m_ulInterval;
	unsigned int		m_uiAmountRepeating;
	CSquirrelArguments*	m_pArguments;
	unsigned long		m_ulNextExecution;
};
