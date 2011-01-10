//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CNetModule.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

typedef bool                     (* VerifyVersion_t)(BYTE byteVersion);
typedef CRakServerInterface *    (* GetRakServerInterface_t)();
typedef void                     (* DestroyRakServerInterface_t)(CRakServerInterface * pRakServer);
typedef CRakClientInterface *    (* GetRakClientInterface_t)();
typedef void                     (* DestroyRakClientInterface_t)(CRakClientInterface * pRakClient);
typedef CNetBitStreamInterface * (* GetBitStreamInterface1_t)();
typedef CNetBitStreamInterface * (* GetBitStreamInterface2_t)(const unsigned int initialBytesToAllocate);
typedef CNetBitStreamInterface * (* GetBitStreamInterface3_t)(unsigned char* _data, const unsigned int lengthInBytes, bool _copyData);
typedef void                     (* DestroyBitStreamInterface_t)(CNetBitStreamInterface * pBitStream);

class CNetModule
{
private:
	static CLibrary *                  m_pLibrary;
	static GetRakServerInterface_t     m_pfnGetRakServerInterface;
	static DestroyRakServerInterface_t m_pfnDestroyRakServerInterface;
	static GetRakClientInterface_t     m_pfnGetRakClientInterface;
	static DestroyRakClientInterface_t m_pfnDestroyRakClientInterface;
	static GetBitStreamInterface1_t    m_pfnGetBitStreamInterface1;
	static GetBitStreamInterface2_t    m_pfnGetBitStreamInterface2;
	static GetBitStreamInterface3_t    m_pfnGetBitStreamInterface3;
	static DestroyBitStreamInterface_t m_pfnDestroyBitStreamInterface;

public:
	CNetModule();
	~CNetModule();

	static bool                     Init();
	static void                     Shutdown();
	static bool                     VerifyVersion(BYTE byteVersion);
	static CRakServerInterface *    GetRakServerInterface();
	static void                     DestroyRakServerInterface(CRakServerInterface * pRakServer);
	static CRakClientInterface *    GetRakClientInterface();
	static void                     DestroyRakClientInterface(CRakClientInterface * pRakClient);
	static CNetBitStreamInterface * GetBitStreamInterface1();
	static CNetBitStreamInterface * GetBitStreamInterface2(const unsigned int initialBytesToAllocate);
	static CNetBitStreamInterface * GetBitStreamInterface3(unsigned char* _data, const unsigned int lengthInBytes, bool _copyData);
	static void                     DestroyBitStreamInterface(CNetBitStreamInterface * pBitStream);
};
