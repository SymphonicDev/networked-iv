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

typedef BYTE                     (* GetNetworkVersion_t)();
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

public:
	CNetModule();
	~CNetModule();

	BYTE                     GetNetworkVersion();
	CRakServerInterface *    GetRakServerInterface();
	void                     DestroyRakServerInterface(CRakServerInterface * pRakServer);
	CRakClientInterface *    GetRakClientInterface();
	void                     DestroyRakClientInterface(CRakClientInterface * pRakClient);
	CNetBitStreamInterface * GetBitStreamInterface1();
	CNetBitStreamInterface * GetBitStreamInterface2(const unsigned int initialBytesToAllocate);
	CNetBitStreamInterface * GetBitStreamInterface3(unsigned char* _data, const unsigned int lengthInBytes, bool _copyData);
	void                     DestroyBitStreamInterface(CNetBitStreamInterface * pBitStream);
};