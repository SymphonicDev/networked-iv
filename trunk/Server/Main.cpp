//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: Main.cpp
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CServer * g_pServer = NULL;

/*void DoTests()
{
	getc(stdin);
#define ITER_COUNT 999999/*9999999*/
	DWORD dwStart = GetTickCount();
	for(size_t i = 0; i < ITER_COUNT; i++)
	{
		String str;
		str.Set("Hello World!");
		str.Set("TROLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");
		str.Set("TROLOL");
	}
	DWORD dwEnd = GetTickCount();
	printf("CString took %dms\n", (dwEnd - dwStart));
	dwStart = GetTickCount();
	for(size_t i = 0; i < ITER_COUNT; i++)
	{
		std::string str;
		str.assign("Hello World!");
		str.assign("TROLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");
		str.assign("TROLOL");
	}
	dwEnd = GetTickCount();
	printf("std::string took %dms\n", (dwEnd - dwStart));
	dwStart = GetTickCount();
	for(size_t i = 0; i < ITER_COUNT; i++)
	{
		String str;
		str.Set("Hello World!");
		str.Set("TROLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");
		str.Set("TROLOL");
	}
	dwEnd = GetTickCount();
	printf("CString took %dms\n", (dwEnd - dwStart));
	dwStart = GetTickCount();
	for(size_t i = 0; i < ITER_COUNT; i++)
	{
		std::string str;
		str.assign("Hello World!");
		str.assign("TROLOLOLOLOLOLOLOLOLOLOLOLOLOLOL");
		str.assign("TROLOL");
	}
	dwEnd = GetTickCount();
	printf("std::string took %dms\n", (dwEnd - dwStart));
	getc(stdin);
	String str;
	printf(str.C_String());
	str.Set("Hello World!\n");
	printf(str.C_String());
	str.Format("Hello %s\n", "World!");
	printf(str.C_String());
	String str2("Hello World!\n");
	printf(str2.C_String());
	String str3("Hello %s\n", "World!");
	printf(str3.C_String());
	printf("1: %d\n", str3.GetLength());
	printf("2: %c\n", str3.GetChar(0));
	printf("3: %d\n", str3.IsEmpty());
	printf("4: %d\n", str3.IsLower());
	str3.ToLower();
	printf("5: %s\n", str3.C_String());
	printf("6: %d\n", str3.IsLower());
	printf("7: %d\n", str3.IsUpper());
	str3.ToUpper();
	printf("8: %s\n", str3.C_String());
	printf("9: %d\n", str3.IsUpper());
	str3.Truncate(6);
	printf("10: %s\n", str3.C_String());
	str3.Append(" World!");
	printf("11: %s\n", str3.C_String());
	str3.Set("Hello World!\n");
	printf("12: %s\n", str3.C_String());
	str3.Insert(6, "Crazy ");
	printf("13: %s\n", str3.C_String());
	printf("14: %d\n", str3.Find("World!"));
	printf("15: %d\n", str3.Find("Test"));
	printf("16: %d\n", str3.Contains("World"));
	printf("17: %d\n", str3.Contains("Test"));
	String str4(str3.C_String());
	printf("18: %d\n", (str3 == str4.C_String()));
	str4.ToLower();
	printf("19: %d\n", (str3 == str4.C_String()));
	printf("20: %d\n", (str3.ICompare(str4.C_String())));
	str3.Set("1337");
	printf("21: %d\n", str3.ToInteger());
	str3.Set("1");
	printf("22: %d\n", str3.ToBoolean());
	str3.Set("0");
	printf("23: %d\n", str3.ToBoolean());
	str3.Set("Hello World!\n");
	printf("24: %s\n", str3.C_String());
	str3.SetChar(0, 'Y');
	printf("25: %s\n", str3.C_String());
	str3.Set("Bla Bla");
	printf("26: %d\n", str3.Find("Bla"));
	printf("27: %d\n", str3.ReverseFind("Bla"));
}*/

int main()
{
	//DoTests();

	// Create the server instance
	g_pServer = new CServer();

	// If the instance creation failed, exit
	if(!g_pServer)
		return 0;

	// Call the server OnLoad event
	g_pServer->OnLoad();

	// Loop until the server IsActive returns false
	while(g_pServer->IsActive())
	{
		// Call the server Process event
		g_pServer->Process();

		// Wait for 10ms
		Sleep(10);
	}

	// Call the server OnUnload event
	g_pServer->OnUnload();

	// Delete the server instance
	SAFE_DELETE(g_pServer);
	return 0;
}
