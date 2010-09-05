//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CClient.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

CGame *           g_pGame = NULL;
CXLiveHook *      g_pXLiveHook = NULL;
CDirect3D9Hook *  g_pDirect3D9Hook = NULL;
CNetModule *      g_pNetModule = NULL;
CNetworkManager * g_pNetworkManager = NULL;
CLocalPlayer *    g_pLocalPlayer = NULL;
CFont *           g_pFont = NULL;
CChatWindow *     g_pChatWindow = NULL;

bool CClient::OnLoad()
{
	// Open the log file
	CLogFile::Open("Client.log");

	CLogFile::Printf("1");

	// Reset the port and set the nick limit
	m_usPort = 0;
	CLogFile::Printf("2");
	m_strNick.SetLimit(NICK_MAX);
	CLogFile::Printf("3");

	// TODO: CCommandLine class
	// TODO: CCommandLine::Parse
	// TODO: CCommandLine::GetOption
	// Process the command line parameters
	char * szCommandLine = GetCommandLine();
	CLogFile::Printf("4");

	while(*szCommandLine)
	{
		CLogFile::Printf("5");
		// Is the current char not a space?
		if(!isspace(*szCommandLine))
		{
			CLogFile::Printf("6");
			// Is the current char a '-'?
			if(*szCommandLine == '-')
			{
				CLogFile::Printf("7");
				// Collect the option string
				String strOption;

				CLogFile::Printf("8");
				while(*szCommandLine && !isspace(*szCommandLine))
				{
					CLogFile::Printf("9");
					strOption += *szCommandLine;
					CLogFile::Printf("10");
					szCommandLine++;
					CLogFile::Printf("11");
				}
				CLogFile::Printf("12");

				// If we have run out of command line to process break out of the loop
				if(!(*szCommandLine))
					break;

				CLogFile::Printf("13");

				// Skip the spaces between the option and the value
				while(*szCommandLine && isspace(*szCommandLine))
					szCommandLine++;

				CLogFile::Printf("14");

				// If we have run out of command line to process break out of the loop
				if(!(*szCommandLine))
					break;

				// Collect the value string
				String strValue;
				// TODO: Check if the value first char is a '-'?

				while(*szCommandLine && !isspace(*szCommandLine))
				{
					strValue += *szCommandLine;
					szCommandLine++;
				}

				// Handle the option and value string
				if(!strcmp(strOption.C_String(), "-ip"))
					m_strIp.Set(strValue.C_String());
				else if(!strcmp(strOption.C_String(), "-port"))
					m_usPort = atoi(strValue.C_String());
				else if(!strcmp(strOption.C_String(), "-password"))
					m_strPassword.Set(strValue.C_String());
				else if(!strcmp(strOption.C_String(), "-nick"))
					m_strNick.Set(strValue.C_String());
				else
				{
					CLogFile::Printf("Warning: Unhandled command line parameter %s (%s)", 
						strOption.C_String(), strValue.C_String());
				}

				// If we have run out of command line to process break out of the loop
				if(!(*szCommandLine))
					break;
			}
		}

		// Increment the command line string pointer
		szCommandLine++;
	}

	// Do we not have an ip or nick?
	if(m_strIp.IsEmpty() || m_strNick.IsEmpty())
	{
		MessageBox(NULL, "Not enough command line parameters specified. Cannot launch Networked: IV.", 
			NULL, NULL);
		return false;
	}

	// Get the application base address
	m_uiBaseAddress = (unsigned int)GetModuleHandle(NULL);

	// If the base address is not valid, exit
	if(!m_uiBaseAddress)
		return false;

	// Subtract the image base from the base address
	m_uiBaseAddress -= 0x400000;

	// Log the base address
	CLogFile::Printf("base address is 0x%p", m_uiBaseAddress);

	// Create the game instance
	g_pGame = new CGame();

	// If the instance creation failed, exit
	if(!g_pGame)
		return false;

	CLogFile::Printf("game instance created");

	// Apply the game patches
	g_pGame->ApplyPatches();

	CLogFile::Printf("game patches applied");

	// Create the xlive hook instance
	g_pXLiveHook = new CXLiveHook();

	// If the instance creation failed, exit
	if(!g_pXLiveHook)
		return false;

	CLogFile::Printf("xlive hook instance created");

	// Install the xlive hook
	g_pXLiveHook->Install();

	CLogFile::Printf("xlive hook installed");

	// Create the d3d9 hook instance
	g_pDirect3D9Hook = new CDirect3D9Hook();

	// If the instance creation failed, exit
	if(!g_pDirect3D9Hook)
		return false;

	CLogFile::Printf("d3d9 instance created");

	// Install the d3d9 hook
	g_pDirect3D9Hook->Install();

	CLogFile::Printf("d3d9 hook installed");

	// Create the net module instance
	g_pNetModule = new CNetModule();

	CLogFile::Printf("net module instance created");

	// Create the network manager instance
	g_pNetworkManager = new CNetworkManager();

	CLogFile::Printf("network manager instance created");

	// Success!
	return true;
}

void CClient::OnUnload()
{
	// Delete the chat window instance
	SAFE_DELETE(g_pChatWindow);

	// Delete the font instance
	SAFE_DELETE(g_pFont);

	// Delete the local player instance
	SAFE_DELETE(g_pLocalPlayer);

	// Delete the network manager instance
	SAFE_DELETE(g_pNetworkManager);

	// Delete the net module instance
	SAFE_DELETE(g_pNetModule);

	// Uninstall the d3d9 hook
	if(g_pDirect3D9Hook)
		g_pDirect3D9Hook->Uninstall();

	// Delete the d3d9 hook instance
	SAFE_DELETE(g_pDirect3D9Hook);

	// Uninstall the xlive hook
	g_pXLiveHook->Uninstall();

	// Delete the xlive hook instance
	SAFE_DELETE(g_pXLiveHook);

	// Close the log file
	CLogFile::Close();
}

unsigned int CClient::GetBaseAddress()
{
	return m_uiBaseAddress;
}

void CClient::OnD3DCreateDevice(IDirect3DDevice9 * pD3DDevice)
{
	CLogFile::Printf("d3d create");
	// Create our font instance
	g_pFont = new CD3DXFont(pD3DDevice, 14, 0, FW_BOLD, "Tahoma");

	// Create out chat window instance
	g_pChatWindow = new CChatWindow(g_pFont);
	//
	g_pChatWindow->Enable();
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Chat window initialized!");
	//
}

void CClient::OnD3DLostDevice(IDirect3DDevice9 * pD3DDevice)
{
	// Does the font exist?
	if(g_pFont)
		// Inform it of the device loss
		g_pFont->OnDeviceLost();
}

void CClient::OnD3DResetDevice(IDirect3DDevice9 * pD3DDevice)
{
	// Does the font exist?
	if(g_pFont)
		// Inform it of the device reset
		g_pFont->OnDeviceReset();
}

void CClient::OnD3DBeginScene(IDirect3DDevice9 * pD3DDevice)
{
	
}

bool bCreatePlayer = false;
CPlayer * pPlayer = NULL;
bool bCreateVehicle = false;
bool bChangeModel = false;

void CClient::OnD3DEndScene(IDirect3DDevice9 * pD3DDevice)
{
	// Testing code
	if(GetAsyncKeyState(VK_F3))
	{
		if(!bCreatePlayer)
		{
			CLogFile::Printf("Creating player...");
			DWORD dwStart = GetTickCount();
			pPlayer = new CPlayer(false);
			pPlayer->Create();
			DWORD dwEnd = GetTickCount();
			CLogFile::Printf("Player created (%dms)!", (dwEnd - dwStart));
		}
		else
		{
			CLogFile::Printf("Destroying player (%d, 0x%p, 0x%p)...", CPools::GetLocalPlayerIndex(), CPools::GetPlayerPedFromIndex(1), CPools::GetPlayerPedFromIndex(0));
			pPlayer->Destroy();
			CLogFile::Printf("Player destroyed (%d, 0x%p, 0x%p)!", CPools::GetLocalPlayerIndex(), CPools::GetPlayerPedFromIndex(1), CPools::GetPlayerPedFromIndex(0));
		}

		bCreatePlayer = !bCreatePlayer;
	}
	else if(GetAsyncKeyState(VK_F4) && !bCreateVehicle)
	{
		CLogFile::Printf("Creating vehicle...");
#define MODEL_SULTANRS 0xEE6024BC
		g_pGame->LoadModel(MODEL_SULTANRS);
		g_pGame->CreateVehicle(MODEL_SULTANRS);
		//unsigned int uVehicleHandle;
		//InvokeNative<void *>(0x2F1D6843, MODEL_SULTANRS, -346.36f, 1144.80f, 14.79f, &uVehicleHandle, true); // CREATE_CAR // MODEL_SULTANRS
		CLogFile::Printf("Vehicle created!");
		bCreateVehicle = true;
	}
	else if(GetAsyncKeyState(VK_F5) && !bChangeModel)
	{
		CLogFile::Printf("Changing model...");
#define MODEL_IG_BRUCIE 0x98E29920
		int iModelIndex = g_pGame->LoadModel(MODEL_IG_BRUCIE);
		CLogFile::Printf("Model loaded");
		DWORD dwFunc = (GetBaseAddress() + /*0x9C0AA0*/0x8AC500); // CPlayerPed::SetModelIndex // CPed::SetModelIndex
		//DWORD dwFunc = (GetBaseAddress() + 0x9C0AA0); // CPlayerPed::SetModelIndex
		IVPlayerPed * pPlayerPed = CPools::GetPlayerPedFromIndex(0);
		IVPed * pPed = pPlayerPed->m_pPed;
		CLogFile::Printf("Calling function...");
		_asm
		{
			push iModelIndex
			//mov ecx, pPlayerPed
			mov ecx, pPed
			call dwFunc
			//add esp, 4
		}
		CLogFile::Printf("Model changed!");
		//InvokeNative<void *>(0x232F1A85, 0, MODEL_IG_BRUCIE); // CHANGE_PLAYER_MODEL // MODEL_IG_BRUCIE
		bChangeModel = true;
	}

	// Does the chat window exist?
	if(g_pChatWindow)
	{
		// Draw it
		g_pChatWindow->Draw();
	}

	// Does the network manager exist?
	if(g_pNetworkManager)
	{
		// Process it
		g_pNetworkManager->Process();
	}
}

void CClient::OnGameLoad()
{
	// Create the local player instance
	g_pLocalPlayer = new CLocalPlayer();

	CLogFile::Printf("local player instance created");

	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Game loaded!");
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Starting network manager...");
	g_pNetworkManager->Startup(m_strIp, m_usPort, m_strPassword);
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Network manager started!");
	g_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Establishing connection to 127.0.0.1:9999...");
	g_pNetworkManager->Connect();
}

String CClient::GetNick()
{
	return m_strNick;
}
