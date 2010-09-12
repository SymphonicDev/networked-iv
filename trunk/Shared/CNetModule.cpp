//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetModule.cpp
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CNetModule::CNetModule()
{
	// Create the library instance
	m_pLibrary = new CLibrary();

	// Get the net module path
	char szPath[MAX_PATH];
	sprintf(szPath, "%sNet" DEBUG_SUFFIX LIBRARY_EXTENSION, SharedUtility::GetAppPath());

	// Load the net module
	if(!m_pLibrary->Load(szPath))
	{
		CLogFile::Printf("Failed to load net module");
		ExitProcess(0);
	}

	// Verify the net module network version
	if(GetNetworkVersion() != NETWORK_VERSION)
	{
		CLogFile::Printf("Invalid net module network version");
		ExitProcess(0);
	}
}

CNetModule::~CNetModule()
{
	// Unload the net module
	m_pLibrary->Unload();

	// Delete the library instance
	SAFE_DELETE(m_pLibrary);
}

BYTE CNetModule::GetNetworkVersion()
{
	// Get a pointer to the GetNetworkVersion function
	GetNetworkVersion_t pfnGetNetworkVersion = (GetNetworkVersion_t)
		m_pLibrary->GetProcedureAddress("GetNetworkVersion");

	// Is the pointer invalid?
	if(!pfnGetNetworkVersion)
		return NULL;

	// Call the GetNetworkVersion function and return the result
	return pfnGetNetworkVersion();
}

CRakServerInterface * CNetModule::GetRakServerInterface()
{
	// Get a pointer to the GetRakServerInterface function
	GetRakServerInterface_t pfnGetRakServerInterface = (GetRakServerInterface_t)
		m_pLibrary->GetProcedureAddress("GetRakServerInterface");

	// Is the pointer invalid?
	if(!pfnGetRakServerInterface)
		return NULL;

	// Call the GetRakServerInterface function
	CRakServerInterface * pRakServer = pfnGetRakServerInterface();

	// Return the RakServer instance
	return pRakServer;
}

void CNetModule::DestroyRakServerInterface(CRakServerInterface * pRakServer)
{
	// Get a pointer to the DestroyRakServerInterface function
	DestroyRakServerInterface_t pfnDestroyRakServerInterface = (DestroyRakServerInterface_t)
		m_pLibrary->GetProcedureAddress("DestroyRakServerInterface");

	// Is the pointer valid?
	if(pfnDestroyRakServerInterface)
	{
		// Call the DestroyRakServerInterface function
		pfnDestroyRakServerInterface(pRakServer);
	}
}

CRakClientInterface * CNetModule::GetRakClientInterface()
{
	// Get a pointer to the GetRakClientInterface function
	GetRakClientInterface_t pfnGetRakClientInterface = (GetRakClientInterface_t)
		m_pLibrary->GetProcedureAddress("GetRakClientInterface");

	// Is the pointer invalid?
	if(!pfnGetRakClientInterface)
		return NULL;

	// Call the GetRakClientInterface function
	CRakClientInterface * pRakClient = pfnGetRakClientInterface();

	// Return the RakClient instance
	return pRakClient;
}

void CNetModule::DestroyRakClientInterface(CRakClientInterface * pRakClient)
{
	// Get a pointer to the DestroyRakServerInterface function
	DestroyRakClientInterface_t pfnDestroyRakClientInterface = (DestroyRakClientInterface_t)
		m_pLibrary->GetProcedureAddress("DestroyRakClientInterface");

	// Is the pointer valid?
	if(pfnDestroyRakClientInterface)
	{
		// Call the DestroyRakClientInterface function
		pfnDestroyRakClientInterface(pRakClient);
	}
}

CNetBitStreamInterface * CNetModule::GetBitStreamInterface1()
{
	// Get a pointer to the GetBitStreamInterface1 function
	GetBitStreamInterface1_t pfnGetBitStreamInterface1 = (GetBitStreamInterface1_t)
		m_pLibrary->GetProcedureAddress("GetBitStreamInterface1");

	// Is the pointer invalid?
	if(!pfnGetBitStreamInterface1)
		return NULL;

	// Call the GetBitStreamInterface1 function
	CNetBitStreamInterface * pBitStream = pfnGetBitStreamInterface1();

	// Return the BitStream instance
	return pBitStream;
}

CNetBitStreamInterface * CNetModule::GetBitStreamInterface2(const unsigned int initialBytesToAllocate)
{
	// Get a pointer to the GetBitStreamInterface2 function
	GetBitStreamInterface2_t pfnGetBitStreamInterface2 = (GetBitStreamInterface2_t)
		m_pLibrary->GetProcedureAddress("GetBitStreamInterface2");

	// Is the pointer invalid?
	if(!pfnGetBitStreamInterface2)
		return NULL;

	// Call the GetBitStreamInterface2 function
	CNetBitStreamInterface * pBitStream = pfnGetBitStreamInterface2(initialBytesToAllocate);

	// Return the BitStream instance
	return pBitStream;
}

CNetBitStreamInterface * CNetModule::GetBitStreamInterface3(unsigned char* _data, const unsigned int lengthInBytes, bool _copyData)
{
	// Get a pointer to the GetBitStreamInterface3 function
	GetBitStreamInterface3_t pfnGetBitStreamInterface3 = (GetBitStreamInterface3_t)
		m_pLibrary->GetProcedureAddress("GetBitStreamInterface3");

	// Is the pointer invalid?
	if(!pfnGetBitStreamInterface3)
		return NULL;

	// Call the GetBitStreamInterface3 function
	CNetBitStreamInterface * pBitStream = pfnGetBitStreamInterface3(_data, lengthInBytes, _copyData);

	// Return the BitStream instance
	return pBitStream;
}

void CNetModule::DestroyBitStreamInterface(CNetBitStreamInterface * pBitStream)
{
	// Get a pointer to the DestroyBitStreamInterface function
	DestroyBitStreamInterface_t pfnDestroyBitStreamInterface = (DestroyBitStreamInterface_t)
		m_pLibrary->GetProcedureAddress("DestroyBitStreamInterface");

	// Is the pointer valid?
	if(pfnDestroyBitStreamInterface)
	{
		// Call the DestroyRakClientInterface function
		pfnDestroyBitStreamInterface(pBitStream);
	}
}
