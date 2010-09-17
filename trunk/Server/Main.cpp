//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: Main.cpp
// Project: Server
// Author(s): jenksta
//            MaVe
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

// NOTE: Wait times in InputThread, main and RakPeer::Startup, should do a define for them (currently 10ms)
// TODO:
// - CHttpClient
// -- CThreadedHttpClient

CServer * g_pServer = NULL;

#ifdef WIN32
BOOL WINAPI CtrlHandler(DWORD dwType)
{
	switch(dwType)
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		g_pServer->OnCloseEvent();
		return TRUE;
	}

	return FALSE;
}
#else
void SignalHandler(int iType)
{
	// NOTE: I don't think param 1 is the signal type
	switch(iType)
	{
	case SIGINT:
	case SIGTERM:
		g_pServer->OnCloseEvent();
	}
}
#endif

void InputThread(CThread * pCreator)
{
	char szInputBuffer[512]; // Buffer MUST be 3 or more (input char, \n, \0)
	String strInputString;

	// Loop until server shutdown
	while(pCreator->GetUserData<bool>())
	{
		// Wait for input from the console
		fgets(szInputBuffer, sizeof(szInputBuffer), stdin);

		// Do we have anything in the input?
		if(szInputBuffer[0] != '\n')
		{
			// Append the input to the input string
			strInputString += szInputBuffer;

			// Get the input string length
			size_t sLength = strInputString.GetLength();

			// Is this the last of the input?
			if(strInputString[sLength - 1] == '\n')
			{
#ifdef WIN32
				// Replace '\n' with '\0'
				strInputString.Truncate(sLength - 1);
#else
				// Replace '\r\n' with '\0'
				strInputString.Truncate(sLength - 2);
#endif

				// Add the input string to the console input queue
				g_pServer->AddToInputQueue(strInputString);

				// Clear the input string
				strInputString.Clear();
			}
		}

		// Wait for 10ms
		Sleep(10);
	}
}

int main()
{
	// Create the server instance
	g_pServer = new CServer();

	if(!g_pServer)
	{
		// Instance creation failed, exit
		return 1;
	}

	// Call the server OnLoad event
	if(!g_pServer->OnLoad())
	{
		// Server load failed, exit
		return 1;
	}

	// Register the close event handler
#ifdef WIN32
	SetConsoleCtrlHandler(CtrlHandler, TRUE);
#else
	void (* prev_fn)(int);
	prev_fn = signal(SIGINT, SignalHandler);
	if(prev_fn == SIG_IGN) signal(SIGINT, SIG_IGN);
	prev_fn = signal(SIGTERM, SignalHandler);
	if(prev_fn == SIG_IGN) signal(SIGTERM, SIG_IGN);
#endif

	// Start the input thread
	CThread inputThread;
	inputThread.SetUserData<bool>(true);
	inputThread.Start(InputThread);

	// Loop until the server IsActive returns false
	while(g_pServer->IsActive())
	{
		// Call the server Process event
		g_pServer->Process();

		// Wait for 10ms
		Sleep(10);
	}

	// Stop the input thread
	inputThread.SetUserData<bool>(false);
	inputThread.Stop();

	// Call the server OnUnload event
	g_pServer->OnUnload();

	// Delete the server instance
	SAFE_DELETE(g_pServer);
	return 0;
}
