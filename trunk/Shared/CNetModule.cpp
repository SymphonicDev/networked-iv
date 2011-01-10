//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetModule.cpp
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CLibrary *                  CNetModule::m_pLibrary;
GetRakServerInterface_t     CNetModule::m_pfnGetRakServerInterface;
DestroyRakServerInterface_t CNetModule::m_pfnDestroyRakServerInterface;
GetRakClientInterface_t     CNetModule::m_pfnGetRakClientInterface;
DestroyRakClientInterface_t CNetModule::m_pfnDestroyRakClientInterface;
GetBitStreamInterface1_t    CNetModule::m_pfnGetBitStreamInterface1;
GetBitStreamInterface2_t    CNetModule::m_pfnGetBitStreamInterface2;
GetBitStreamInterface3_t    CNetModule::m_pfnGetBitStreamInterface3;
DestroyBitStreamInterface_t CNetModule::m_pfnDestroyBitStreamInterface;

CNetModule::CNetModule()
{

}

CNetModule::~CNetModule()
{

}

bool CNetModule::Init()
{
	// Create the library instance
	m_pLibrary = new CLibrary();

	// Get the net module path
	String strPath("%sNet" DEBUG_SUFFIX LIBRARY_EXTENSION, SharedUtility::GetAppPath());

	// Load the net module
	if(!m_pLibrary->Load(strPath.C_String()))
	{
		CLogFile::Printf("Failed to load net module");
		return false;
	}

	// Verify the net module version
	if(!VerifyVersion(NETWORK_MODULE_VERSION))
	{
		CLogFile::Printf("Invalid net module version");
		return false;
	}

	// Get pointers to the net module functions
	m_pfnGetRakServerInterface = (GetRakServerInterface_t)m_pLibrary->GetProcedureAddress("GetRakServerInterface");
	m_pfnDestroyRakServerInterface = (DestroyRakServerInterface_t)m_pLibrary->GetProcedureAddress("DestroyRakServerInterface");
	m_pfnGetRakClientInterface = (GetRakClientInterface_t)m_pLibrary->GetProcedureAddress("GetRakClientInterface");
	m_pfnDestroyRakClientInterface = (DestroyRakClientInterface_t)m_pLibrary->GetProcedureAddress("DestroyRakClientInterface");
	m_pfnGetBitStreamInterface1 = (GetBitStreamInterface1_t)m_pLibrary->GetProcedureAddress("GetBitStreamInterface1");
	m_pfnGetBitStreamInterface2 = (GetBitStreamInterface2_t)m_pLibrary->GetProcedureAddress("GetBitStreamInterface2");
	m_pfnGetBitStreamInterface3 = (GetBitStreamInterface3_t)m_pLibrary->GetProcedureAddress("GetBitStreamInterface3");
	m_pfnDestroyBitStreamInterface = (DestroyBitStreamInterface_t)m_pLibrary->GetProcedureAddress("DestroyBitStreamInterface");

	// Verify the pointers to the net module functions
	if(!m_pfnGetRakServerInterface || !m_pfnDestroyRakServerInterface || !m_pfnGetRakClientInterface || 
		!m_pfnDestroyRakClientInterface || !m_pfnGetBitStreamInterface1 || !m_pfnGetBitStreamInterface2 || 
		!m_pfnGetBitStreamInterface3 || !m_pfnDestroyBitStreamInterface)
	{
		CLogFile::Printf("Net module is corrupt");
		return false;
	}

	return true;
}

void CNetModule::Shutdown()
{
	// Unload the net module
	m_pLibrary->Unload();

	// Delete the library instance
	SAFE_DELETE(m_pLibrary);
}

bool CNetModule::VerifyVersion(BYTE byteVersion)
{
	// Get a pointer to the VerifyVersion function
	VerifyVersion_t pfnVerifyVersion = (VerifyVersion_t)m_pLibrary->GetProcedureAddress("VerifyVersion");

	// Is the pointer invalid?
	if(!pfnVerifyVersion)
		return false;

	// Call the VerifyVersion function and return the result
	return pfnVerifyVersion(byteVersion);
}

CRakServerInterface * CNetModule::GetRakServerInterface()
{
	// Call the GetRakServerInterface function
	CRakServerInterface * pRakServer = m_pfnGetRakServerInterface();

	// Return the RakServer instance
	return pRakServer;
}

void CNetModule::DestroyRakServerInterface(CRakServerInterface * pRakServer)
{
	// Call the DestroyRakServerInterface function
	m_pfnDestroyRakServerInterface(pRakServer);
}

CRakClientInterface * CNetModule::GetRakClientInterface()
{
	// Call the GetRakClientInterface function
	CRakClientInterface * pRakClient = m_pfnGetRakClientInterface();

	// Return the RakClient instance
	return pRakClient;
}

void CNetModule::DestroyRakClientInterface(CRakClientInterface * pRakClient)
{
	// Call the DestroyRakClientInterface function
	m_pfnDestroyRakClientInterface(pRakClient);
}

CNetBitStreamInterface * CNetModule::GetBitStreamInterface1()
{
	// Call the GetBitStreamInterface1 function
	CNetBitStreamInterface * pBitStream = m_pfnGetBitStreamInterface1();

	// Return the BitStream instance
	return pBitStream;
}

CNetBitStreamInterface * CNetModule::GetBitStreamInterface2(const unsigned int initialBytesToAllocate)
{
	// Call the GetBitStreamInterface2 function
	CNetBitStreamInterface * pBitStream = m_pfnGetBitStreamInterface2(initialBytesToAllocate);

	// Return the BitStream instance
	return pBitStream;
}

CNetBitStreamInterface * CNetModule::GetBitStreamInterface3(unsigned char* _data, const unsigned int lengthInBytes, bool _copyData)
{
	// Call the GetBitStreamInterface3 function
	CNetBitStreamInterface * pBitStream = m_pfnGetBitStreamInterface3(_data, lengthInBytes, _copyData);

	// Return the BitStream instance
	return pBitStream;
}

void CNetModule::DestroyBitStreamInterface(CNetBitStreamInterface * pBitStream)
{
	// Call the DestroyRakClientInterface function
	m_pfnDestroyBitStreamInterface(pBitStream);
}
