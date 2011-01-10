//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CClient.cpp
// Project: Client
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

bool CClient::OnLoad()
{
	// Open the log file
	CLogFile::Open("Client.log");

	// Install our exception handler
	CExceptionHandler::Install();

	// Reset the class object pointers
	m_pGame = NULL;
	m_pXLiveHook = NULL;
	m_pDirect3D9Hook = NULL;
	m_pNetworkManager = NULL;
	m_pLocalPlayer = NULL;
	m_pPlayerManager = NULL;
	m_pFont = NULL;
	m_pChatWindow = NULL;

	// Reset the port and set the nick limit
	m_usPort = 0;
	m_strNick.SetLimit(NICK_MAX);

	// TODO: CCommandLine class
	// TODO: CCommandLine::Parse
	// TODO: CCommandLine::GetOption
	// Process the command line parameters
	char * szCommandLine = GetCommandLine();

	while(*szCommandLine)
	{
		// Is the current char not a space?
		if(!isspace(*szCommandLine))
		{
			// Is the current char a '-'?
			if(*szCommandLine == '-')
			{
				// Collect the option string
				String strOption;

				while(*szCommandLine && !isspace(*szCommandLine))
				{
					strOption += *szCommandLine;
					szCommandLine++;
				}

				// If we have run out of command line to process break out of the loop
				if(!(*szCommandLine))
					break;

				// Skip the spaces between the option and the value
				while(*szCommandLine && isspace(*szCommandLine))
					szCommandLine++;

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
	m_pGame = new CGame();

	// If the instance creation failed, exit
	if(!m_pGame)
		return false;

	CLogFile::Printf("game instance created");

	// Apply the game patches
	m_pGame->ApplyPatches();

	CLogFile::Printf("game patches applied");

	// Create the xlive hook instance
	m_pXLiveHook = new CXLiveHook();

	// If the instance creation failed, exit
	if(!m_pXLiveHook)
		return false;

	CLogFile::Printf("xlive hook instance created");

	// Install the xlive hook
	m_pXLiveHook->Install();

	CLogFile::Printf("xlive hook installed");

	// Create the d3d9 hook instance
	m_pDirect3D9Hook = new CDirect3D9Hook();

	// If the instance creation failed, exit
	if(!m_pDirect3D9Hook)
		return false;

	CLogFile::Printf("d3d9 instance created");

	// Install the d3d9 hook
	m_pDirect3D9Hook->Install();

	CLogFile::Printf("d3d9 hook installed");

	// Initialize the net module, if it fails, exit
	if(!CNetModule::Init())
	{
		CLogFile::Printf("Failed to initialize the net module");
		return false;
	}

	CLogFile::Printf("net module initialized");

	// Create the network manager instance
	m_pNetworkManager = new CNetworkManager();

	CLogFile::Printf("network manager instance created");

	// Success!
	return true;
}

void CClient::OnUnload()
{
	// Delete the chat window instance
	SAFE_DELETE(m_pChatWindow);

	// Delete the font instance
	SAFE_DELETE(m_pFont);

	// Delete the player manager instance
	SAFE_DELETE(m_pPlayerManager);

	// Delete the local player instance
	SAFE_DELETE(m_pLocalPlayer);

	// Delete the network manager instance
	SAFE_DELETE(m_pNetworkManager);

	// Shutdown the net module
	CNetModule::Shutdown();

	// Uninstall the d3d9 hook
	if(m_pDirect3D9Hook)
		m_pDirect3D9Hook->Uninstall();

	// Delete the d3d9 hook instance
	SAFE_DELETE(m_pDirect3D9Hook);

	// Uninstall the xlive hook
	m_pXLiveHook->Uninstall();

	// Delete the xlive hook instance
	SAFE_DELETE(m_pXLiveHook);

	// Close the log file
	CLogFile::Close();
}

void CClient::OnD3DCreateDevice(IDirect3DDevice9 * pD3DDevice)
{
	CLogFile::Printf("d3d create");
	// Create our font instance
	m_pFont = new CD3DXFont(pD3DDevice, 14, 0, FW_BOLD, "Tahoma");

	// Create out chat window instance
	m_pChatWindow = new CChatWindow(m_pFont);
	m_pChatWindow->Enable();
	m_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Chat window initialized!");
}

void CClient::OnD3DLostDevice(IDirect3DDevice9 * pD3DDevice)
{
	// Does the font exist?
	if(m_pFont)
	{
		// Inform it of the device loss
		m_pFont->OnDeviceLost();
	}
}

void CClient::OnD3DResetDevice(IDirect3DDevice9 * pD3DDevice)
{
	// Does the font exist?
	if(m_pFont)
	{
		// Inform it of the device reset
		m_pFont->OnDeviceReset();
	}
}

void CClient::OnD3DBeginScene(IDirect3DDevice9 * pD3DDevice)
{
	
}

bool bCreatePlayer = false;
CPlayer * pPlayers[32];
bool bChangeModel = false;

void CClient::OnD3DEndScene(IDirect3DDevice9 * pD3DDevice)
{
	// Testing code
	if(GetAsyncKeyState(VK_F3))
	{
		if(!bCreatePlayer)
		{
			for(BYTE i = 1; i < 32; i++)
			{
				CLogFile::Printf("Creating player...");
				DWORD dwStart = GetTickCount();
				pPlayers[i] = new CPlayer(false);
				pPlayers[i]->Create();
				DWORD dwEnd = GetTickCount();
				CLogFile::Printf("Player created (%dms)!", (dwEnd - dwStart));
			}
		}
		else
		{
			for(BYTE i = 1; i < 32; i++)
			{
				CLogFile::Printf("Destroying player...");
				pPlayers[i]->Destroy();
				CLogFile::Printf("Player destroyed!");
				delete pPlayers[i];
				CLogFile::Printf("Player deleted!");
			}
		}

		bCreatePlayer = !bCreatePlayer;
	}
	else if(GetAsyncKeyState(VK_F5) && !bChangeModel)
	{
		CLogFile::Printf("Changing model...");
#define MODEL_IG_BRUCIE 0x98E29920
		int iModelIndex = m_pGame->LoadModel(MODEL_IG_BRUCIE);
		CLogFile::Printf("Model loaded");
#define FUNC_CPlayerPed__SetModelIndex 0x9C0AA0
		DWORD dwFunc = (GetBaseAddress() + FUNC_CPlayerPed__SetModelIndex);
		IVPlayerInfo * pPlayerInfo = CPools::GetPlayerInfoFromIndex(0);
		IVPlayerPed * pPlayerPed = pPlayerInfo->m_pPlayerPed;
		CLogFile::Printf("Calling function...");
		_asm
		{
			push iModelIndex
			mov ecx, pPlayerPed
			call dwFunc
			add esp, 4
		}
		CLogFile::Printf("Model changed!");
		//InvokeNative<void *>(0x232F1A85, 0, MODEL_IG_BRUCIE); // CHANGE_PLAYER_MODEL // MODEL_IG_BRUCIE
		bChangeModel = true;
	}

	// Does the chat window exist?
	if(m_pChatWindow)
	{
		// Draw it
		m_pChatWindow->Draw();
	}

	// Does the network manager exist?
	if(m_pNetworkManager)
	{
		// Process it
		m_pNetworkManager->Process();
	}
}

void CClient::OnGameLoad()
{
	// Create the local player instance
	m_pLocalPlayer = new CLocalPlayer();

	CLogFile::Printf("local player instance created");

	// Create the player manager instance
	m_pPlayerManager = new CPlayerManager();

	CLogFile::Printf("player manager instance created");

	m_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Game loaded!");
	m_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Starting network manager...");
	m_pNetworkManager->Startup(m_strIp, m_usPort, m_strPassword);
	m_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Network manager started!");
	m_pChatWindow->OutputMessage(MESSAGE_INFO_COLOR, "Establishing connection to %s:%d...", m_strIp.C_String(), m_usPort);
	m_pNetworkManager->Connect();
}
