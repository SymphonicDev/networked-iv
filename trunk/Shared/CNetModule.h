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
	CLibrary * m_pLibrary;
	GetRakServerInterface_t m_pfnGetRakServerInterface;
	DestroyRakServerInterface_t m_pfnDestroyRakServerInterface;
	GetRakClientInterface_t m_pfnGetRakClientInterface;
	DestroyRakClientInterface_t m_pfnDestroyRakClientInterface;
	GetBitStreamInterface1_t m_pfnGetBitStreamInterface1;
	GetBitStreamInterface2_t m_pfnGetBitStreamInterface2;
	GetBitStreamInterface3_t m_pfnGetBitStreamInterface3;
	DestroyBitStreamInterface_t m_pfnDestroyBitStreamInterface;

public:
	CNetModule();
	~CNetModule();

	bool                     VerifyVersion(BYTE byteVersion);
	CRakServerInterface *    GetRakServerInterface();
	void                     DestroyRakServerInterface(CRakServerInterface * pRakServer);
	CRakClientInterface *    GetRakClientInterface();
	void                     DestroyRakClientInterface(CRakClientInterface * pRakClient);
	CNetBitStreamInterface * GetBitStreamInterface1();
	CNetBitStreamInterface * GetBitStreamInterface2(const unsigned int initialBytesToAllocate);
	CNetBitStreamInterface * GetBitStreamInterface3(unsigned char* _data, const unsigned int lengthInBytes, bool _copyData);
	void                     DestroyBitStreamInterface(CNetBitStreamInterface * pBitStream);
};
