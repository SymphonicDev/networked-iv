//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: Main.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CClient * g_pClient = NULL;

//
// TODO: CException and add a class like this for the server too
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#include <tlhelp32.h>

const char * ExceptionCodeToString(DWORD dwExceptionCode)
{
	switch(dwExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION: return "Access Violation";
	case EXCEPTION_DATATYPE_MISALIGNMENT: return "Datatype Misalignment";
	case EXCEPTION_BREAKPOINT: return "Breakpoint";
	case EXCEPTION_SINGLE_STEP: return "Single Step";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "Array Bounds Exceeded";
	case EXCEPTION_FLT_DENORMAL_OPERAND: return "Float: Denormal Operand";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "Float: Divide By Zero";
	case EXCEPTION_FLT_INEXACT_RESULT: return "Float: Inexact Result";
	case EXCEPTION_FLT_INVALID_OPERATION: return "Float: Invalid Operation";
	case EXCEPTION_FLT_OVERFLOW: return "Float: Overflow";
	case EXCEPTION_FLT_STACK_CHECK: return "Float: Stack Check";
	case EXCEPTION_FLT_UNDERFLOW: return "Float: Underflow";
	case EXCEPTION_INT_DIVIDE_BY_ZERO: return "Integer: Divide By Zero";
	case EXCEPTION_INT_OVERFLOW: return "Integer: Overflow";
	case EXCEPTION_PRIV_INSTRUCTION: return "Priv Instruction";
	case EXCEPTION_IN_PAGE_ERROR: return "In Page Error";
	case EXCEPTION_ILLEGAL_INSTRUCTION: return "Illegal Instruction";
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "Non-continuable Exception";
	case EXCEPTION_STACK_OVERFLOW: return "Stack Overflow";
	case EXCEPTION_INVALID_DISPOSITION: return "Invalid Disposition";
	case EXCEPTION_GUARD_PAGE: return "Guard Page";
	case EXCEPTION_INVALID_HANDLE: return "Invalid Handle";
	case 0xC0000194L: return "Possible Deadlock";
	}

	return "Unknown";
}

bool WriteMiniDump(_EXCEPTION_POINTERS * exceptionPointers)
{
	// Get the application path
	String sMiniDumpPath(SharedUtility::GetAppPath());

	// Get the current system time
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);

	// Append the file name and system type to the application path string
	sMiniDumpPath.AppendF("crashdump-%02d.%02d.%02d-%02d.%02d.%04d.dmp", systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wDay, systemTime.wMonth, systemTime.wYear);

	// Open the minidump file
	HANDLE hFile = CreateFileA(sMiniDumpPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL , NULL);

	// Did we open the minidump file?
	if(hFile)
	{
		// Create the minidump exception information
		MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
		exceptionInfo.ThreadId = GetCurrentThreadId();
		exceptionInfo.ExceptionPointers = exceptionPointers;
		exceptionInfo.ClientPointers = FALSE;

		// Write the minidump to the minidump file
		bool bWritten = (MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, 
			&exceptionInfo, NULL, NULL) != 0);

		// Close the minidump file
		CloseHandle(hFile);

		return bWritten;
	}

	// Failed to open the minidump file
	return false;
}

void DumpExceptionInformation(_EXCEPTION_POINTERS * ExceptionInfo, String * strDestination)
{
	// Append the exception code and exception code string to the exception string
	strDestination->AppendF("Exception code: 0x%p (%s)\n", ExceptionInfo->ExceptionRecord->ExceptionCode, 
		ExceptionCodeToString(ExceptionInfo->ExceptionRecord->ExceptionCode));

	// If we have integer context information then append it to the exception string
	if(ExceptionInfo->ContextRecord->ContextFlags & CONTEXT_INTEGER)
	{
		strDestination->AppendF("Edi: 0x%p Esi: 0x%p Ebx: 0x%p\n", ExceptionInfo->ContextRecord->Edi, 
			ExceptionInfo->ContextRecord->Esi, ExceptionInfo->ContextRecord->Ebx);
		strDestination->AppendF("Edx: 0x%p Ecx: 0x%p Eax: 0x%p\n", ExceptionInfo->ContextRecord->Edx, 
			ExceptionInfo->ContextRecord->Ecx, ExceptionInfo->ContextRecord->Eax);
	}

	// If we have control context information then append it to the exception string
	if(ExceptionInfo->ContextRecord->ContextFlags & CONTEXT_CONTROL)
	{
		strDestination->AppendF("Ebp: 0x%p Eip: 0x%p Esp: 0x%p\n", ExceptionInfo->ContextRecord->Ebp, 
			ExceptionInfo->ContextRecord->Eip, ExceptionInfo->ContextRecord->Esp);
	}
}

bool DumpModules(String * strDestination)
{
	// Create a tool help 32 process snapshot
	HANDLE hModuleSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());

	if(hModuleSnapShot)
	{
		MODULEENTRY32 ModuleEntry;
		ModuleEntry.dwSize = sizeof(ModuleEntry);

		if(Module32First(hModuleSnapShot, &ModuleEntry))
		{
			// Enumerate through all modules
			while(Module32Next(hModuleSnapShot, &ModuleEntry))
			{
				// Append the module information to the exception string
				strDestination->AppendF("Module: (%s) Base address: (0x%p)\n", ModuleEntry.szModule, ModuleEntry.modBaseAddr);
			}
		}

		// Close the snapshot handle
		CloseHandle(hModuleSnapShot);

		return true;
	}

	return false;
}

long WINAPI ExceptionHandler(_EXCEPTION_POINTERS * ExceptionInfo)
{
	// Write the minidump file
	bool bMinidump = WriteMiniDump(ExceptionInfo);

	// Create the exception string with the exception address
	String strException("Version identifier: " MOD_VERSION_STRING "\n");

	strException.AppendF("Exception address: 0x%p\n", ExceptionInfo->ContextRecord->Eip);

	// Append the game base to the exception string
	strException.AppendF("Client base: 0x%p\n", g_pClient->GetBaseAddress());

	// Dump exception information to the exception string
	DumpExceptionInformation(ExceptionInfo, &strException);

	// Append the local player id to the exception string
	strException.AppendF("Local player id: %d\n", CPools::GetLocalPlayerIndex());

	// Append weather or not the minidump was written to the exception string
	strException.AppendF("Minidump written?: %s\n", (bMinidump) ? "Yes" : "No");

	// Save the current exception string for the exception message box
	String strMessageBoxException = strException;

	// Dump modules to the exception string
	DumpModules(&strException);

	// Open the crash information file
	FILE * fCrashInformation = fopen(String("%scrashinfo.txt", SharedUtility::GetAppPath()), "a");

	// Did we open the crash information file?
	if(fCrashInformation)
	{
		// Write the crash heading
		fprintf(fCrashInformation, "\n"
								   "--------------------------------------------------------------------\n"
								   "\n");

		// Write the exception information
		fprintf(fCrashInformation, strException.C_String());

		// Close the crash information file
		fclose(fCrashInformation);
	}

	// Show the desktop
	SetForegroundWindow(HWND_DESKTOP);

	// Show the crash message box
	MessageBox(NULL, strMessageBoxException.C_String(), "IV:MP has crashed", (MB_OK | MB_ICONERROR));

	// Terminate the current process
	TerminateProcess(GetCurrentProcess(), 0);
	return 1;
}
//

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, void *)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			// Disable thread calls
			DisableThreadLibraryCalls(hModule);

			// Install the exception filter
			SetUnhandledExceptionFilter(ExceptionHandler);

			// Create the client instance
			g_pClient = new CClient();

			// If the client instance was created call the client OnLoad function, if
			// it wasn't, exit
			if(!g_pClient || !g_pClient->OnLoad())
			{
				// Something bad happened, exit
				ExitProcess(0);
			}
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			// Call the client OnUnload
			g_pClient->OnUnload();

			// Delete the client instance
			SAFE_DELETE(g_pClient);
		}
		break;
	}

	return TRUE;
}
