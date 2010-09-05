//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: InvokeNative.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//          Contains zlib licensed code from ScriptHook by aru
//
//==========================================================================

#include <StdInc.h>

extern CClient * g_pClient;

void InvokeNativeInternal(unsigned int uHash, NativeContext * pContext)
{
	DWORD dwFunction = (g_pClient->GetBaseAddress() + FUNC_ScrVM__FindNativeAddress_7);
	_asm
	{
		xor eax, eax
		push esi
		mov esi, uHash
		call dwFunction
		pop esi
		test eax, eax
		jz invalid
		push pContext
		call eax
		add esp, 4
invalid:
		ret
	}
}
