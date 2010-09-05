//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: SharedUtility.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

namespace SharedUtility
{
// Strip a path back to the last '\' ('/')
bool StripPath1(char * szString);

// Return the stripped path from a string
// pointer but don't edit the actual pointer
char * StripPath2(char * szString);

// Get the application's path
const char * GetAppPath();

#ifdef WIN32
// Inject the library into the specified process
int InjectLibraryIntoProcess(HANDLE hProcess, char * szLibraryPath);

// Get the process id's handle then inject the library into it
int InjectLibraryIntoProcess(DWORD dwProcessId, char * szLibraryPath);

// Read a string from the registry
bool ReadRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, const char * szDefault, char * szData, DWORD dwSize);

// Write a string to the registry
bool WriteRegistryString(HKEY hKeyLocation, const char * szSubKey, const char * szKey, char * szData, DWORD dwSize);

// Convert an Ansi string to a Unicode string
int AnsiToUnicode(char * szAnsiString, size_t sAnsiStringLength, wchar_t * wszUnicodeString, size_t sUnicodeStringLength, DWORD dwFlags = NULL);
#endif
};
