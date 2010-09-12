//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: SharedUtility.cpp
// Project: Shared
// Author(s): jenksta
//            MaVe
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

namespace SharedUtility
{
bool StripPath1(char * szString)
{
	for(size_t i = strlen(szString); i > 0; --i)
	{
#ifdef WIN32
		if(szString[i] == '\\')
#else
		if(szString[i] == '/')
#endif
		{
			szString[i + 1] = '\0';
			return true;
		}
	}

	return false;
}

char * StripPath2(char * szString)
{
	char * szPath = szString;
	char * szStrippedPath = (szString + strlen(szString));

	while(szStrippedPath != szPath)
	{
#ifdef WIN32
		if(*szStrippedPath == '\\')
#else
		if(*szStrippedPath == '/')
#endif
			return (szStrippedPath + 1);

		szStrippedPath--;
	}

	return szPath;
}

const char * GetAppPath()
{
#ifdef WIN32
	static unsigned int nDummy;
#endif
	static char szAppPath[MAX_PATH];
#ifdef WIN32
	HMODULE hModuleHandle;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, 
		(LPCSTR)&nDummy, &hModuleHandle);
	GetModuleFileName(hModuleHandle, szAppPath, MAX_PATH);
#else
	readlink("/proc/self/exe", szAppPath, MAX_PATH);
#endif
	StripPath1(szAppPath);
	return szAppPath;
}

#ifdef WIN32
int InjectLibraryIntoProcess(HANDLE hProcess, char * szLibraryPath)
{
	int iReturn = 0;

	// Get the length of the library path
	size_t sLibraryPathLen = (strlen(szLibraryPath) + 1);

	// Allocate the a block of memory in our target process for the library path
	void * pRemoteLibraryPath = VirtualAllocEx(hProcess, NULL, sLibraryPathLen, MEM_COMMIT, PAGE_READWRITE);

	// Write our library path to the allocated block of memory
	SIZE_T sBytesWritten = 0;
	WriteProcessMemory(hProcess, pRemoteLibraryPath, (void *)szLibraryPath, sLibraryPathLen, &sBytesWritten);

	if(sBytesWritten != sLibraryPathLen)
	{
		// Failed to write the library path
		iReturn = 1;
	}
	else
	{
		// Get the handle of Kernel32.dll
		HMODULE hKernel32 = GetModuleHandle("Kernel32");

		// Get the address of the LoadLibraryA function from Kernel32.dll
		FARPROC pfnLoadLibraryA = GetProcAddress(hKernel32, "LoadLibraryA");

		// Create a thread inside the target process to load our library
		HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pfnLoadLibraryA, pRemoteLibraryPath, 0, NULL);

		if(hThread)
		{
			// Wait for the created thread to end
			WaitForSingleObject(hThread, INFINITE);

			// Close our thread handle
			CloseHandle(hThread);
		}
		else
		{
			// Thread creation failed
			iReturn = 2;
		}
	}

	// Free the allocated block of memory inside the target process
	VirtualFreeEx(hProcess, pRemoteLibraryPath, sizeof(pRemoteLibraryPath), MEM_RELEASE);

	return iReturn;
}

int InjectLibraryIntoProcess(DWORD dwProcessId, char * szLibraryPath)
{
	// Open our target process
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

	if(!hProcess)
	{
		// Failed to open the process
		return 3;
	}

	// Inject the library into the process
	int iReturn = InjectLibraryIntoProcess(hProcess, szLibraryPath);

	// Close the process handle
	CloseHandle(hProcess);

	return iReturn;
}

bool ReadRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, const char * szDefault, char * szData, DWORD dwSize)
{
	HKEY hKey = NULL;

	if(RegOpenKeyEx(hKeyLocation, szSubKey, NULL, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		LONG lStatus = RegQueryValueEx(hKey, szKey, NULL, &dwType, (BYTE *)szData, &dwSize);
		RegCloseKey(hKey);
		return (lStatus == ERROR_SUCCESS);
	}

	if(szDefault)
		strncpy(szData, szDefault, dwSize);

	return false;
}

bool WriteRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, char * szData, DWORD dwSize)
{
	HKEY hKey = NULL;
	RegOpenKeyEx(hKeyLocation, szSubKey, NULL, KEY_WRITE, &hKey);

	if(!hKey)
		RegCreateKey(hKeyLocation, szSubKey, &hKey);

	if(hKey)
	{
		DWORD dwType = REG_SZ;
		RegSetValueEx(hKey, szKey, NULL, dwType, (BYTE *)szData, dwSize);
		RegCloseKey(hKey);
		return true;
	}

	return false;
}

int AnsiToUnicode(char * szAnsiString, size_t sAnsiStringLength, wchar_t * wszUnicodeString, size_t sUnicodeStringLength, DWORD dwFlags)
{
	return MultiByteToWideChar(CP_ACP, dwFlags, szAnsiString, sAnsiStringLength, wszUnicodeString, sUnicodeStringLength);
}
#endif

const char * GetTimeAndDate()
{
	time_t timeValue;
	time(&timeValue);
	return ctime(&timeValue);
}

const char * GetTime()
{
	static char szTime[256];
	time_t t = time(NULL);
	const struct tm * tm = localtime(&t);
	strftime(szTime, sizeof(szTime), "%H:%M:%S", tm);
	return szTime;
}
};
