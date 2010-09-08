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

int main()
{
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
