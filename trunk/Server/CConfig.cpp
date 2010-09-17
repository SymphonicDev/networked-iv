//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CConfig.cpp
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CConfig::CConfig()
{
	m_pXML = new CXML();
}

CConfig::~CConfig()
{
	SAFE_DELETE(m_pXML);
}

bool CConfig::Open(String strFileName)
{
	return m_pXML->load(strFileName);
}

bool CConfig::GetValueAsString(String strKey, String * strValue)
{
	if(m_pXML->findNode(strKey.C_String()))
	{
		strValue->Set(m_pXML->nodeContent());
		m_pXML->nodeToRoot();
		return true;
	}

	return false;
}

bool CConfig::GetValueAsInteger(String strKey, int * iValue)
{
	if(m_pXML->findNode(strKey.C_String()))
	{
		*iValue = atoi(m_pXML->nodeContent());
		m_pXML->nodeToRoot();
		return true;
	}

	return false;
}

bool CConfig::GetValueFloat(String strKey, float * fValue)
{
	if(m_pXML->findNode(strKey.C_String()))
	{
		*fValue = (float)atof(m_pXML->nodeContent());
		m_pXML->nodeToRoot();
		return true;
	}

	return false;
}

bool CConfig::GetValueAsBoolean(String strKey, bool * bValue)
{
	if(m_pXML->findNode(strKey.C_String()))
	{
		if(!strcmp(m_pXML->nodeContent(), "true"))
		{
			*bValue = true;
		}
		else if(!strcmp(m_pXML->nodeContent(), "false"))
		{
			*bValue = false;
		}
		else
		{
			*bValue = atob(m_pXML->nodeContent());
		}

		m_pXML->nodeToRoot();
		return true;
	}

	return false;
}
