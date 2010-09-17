//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CServer.cpp
// Project: Server
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

#ifdef WIN32
#define SERVER_TITLE "Networked: IV Server"
#endif

CConfig *         g_pConfig = NULL;
CNetModule *      g_pNetModule = NULL;
CNetworkManager * g_pNetworkManager = NULL;
CPlayerManager *  g_pPlayerManager = NULL;

CServer::CServer()
{
	m_bActive = true;
	m_bShowFPS = true;
	m_dwLastFPSUpdateTickCount = 0;
	m_dwFrameCount = 0;
	m_dwFramesPerSecond = 0;
}

CServer::~CServer()
{

}

bool CServer::OnLoad()
{
	// Open the log file
	CLogFile::Open("Server.log", true);

	CLogFile::Printf("Starting up server");

	// Create the config instance
	g_pConfig = new CConfig();

	if(!g_pConfig)
	{
		CLogFile::Printf("Failed to create config instance");
		return false;
	}

	CLogFile::Printf("Config instance created");

	// Open the config file
	if(!g_pConfig->Open("Server.conf"))
	{
		CLogFile::Printf("Failed to open config file, Settings will default to appropriate values.");
	}
	else
	{
		CLogFile::Printf("Config file opened");
	}

	// Create the net module instance
	g_pNetModule = new CNetModule();

	if(!g_pNetModule)
	{
		CLogFile::Printf("Failed to create net module instance");
		return false;
	}

	CLogFile::Printf("Net module instance created");

	// Create the network manager instance
	g_pNetworkManager = new CNetworkManager();

	if(!g_pNetworkManager)
	{
		CLogFile::Printf("Failed to create network manager instance");
		return false;
	}

	CLogFile::Printf("Network manager instance created");

	// Create the player manager instance
	g_pPlayerManager = new CPlayerManager();

	if(!g_pPlayerManager)
	{
		CLogFile::Printf("Failed to create player manager instance");
	}

	CLogFile::Printf("Player manager instance created");

	// Get server port
	int iServerPort = 9999;

	if(!g_pConfig->GetValueAsInteger("Port", &iServerPort))
	{
		CLogFile::Printf("Failed to get 'Port' value from config, defaulting to '9999'");
	}
	else
	{
		CLogFile::Printf("Got 'Port' value '%d' from config", iServerPort);
	}

	// Get show fps
	if(!g_pConfig->GetValueAsBoolean("ShowFPS", &m_bShowFPS))
	{
		CLogFile::Printf("Failed to get 'ShowFPS' value from config, defaulting to 'true'");
	}
	else
	{
		CLogFile::Printf("Got 'ShowFPS' value '%s' from config", m_bShowFPS ? "true" : "false");
	}

	// Start up the network manager
	g_pNetworkManager->Startup(iServerPort, PLAYER_MAX);

	CLogFile::Printf("Network manager started up");

	// Set the server title
#ifdef WIN32
	SetTitle(SERVER_TITLE);
#endif

	CLogFile::Printf("Server started");

	return true;
}

void CServer::Process()
{
	// Is show fps enabled?
	if(m_bShowFPS)
	{
		// Get the current tick count
		DWORD dwTickCount = GetTickCount();

		// Get the amount of time elapsed since the last fps update
		DWORD dwTimeElapsed = (dwTickCount - m_dwLastFPSUpdateTickCount);

		// Update the fps if a second or more has passed
		if(dwTimeElapsed >= 1000)
		{
			// Set the fps
			m_dwFramesPerSecond = m_dwFrameCount;

			// Set the server title
#ifdef WIN32
			String strTitle(SERVER_TITLE " - FPS: %d", m_dwFramesPerSecond);
			SetTitle(strTitle.C_String());
#endif

			// Reset the frame count
			m_dwFrameCount = 0;

			// Set the last fps update tick count
			m_dwLastFPSUpdateTickCount = dwTickCount;
		}

		// Increment the frame count
		m_dwFrameCount++;
	}

	// Process the network manager
	g_pNetworkManager->Process();

	// Process the input queue
	ProcessInputQueue();
}

void CServer::OnUnload()
{
	CLogFile::Printf("Server exiting...");

	// Delete the player manager instance
	SAFE_DELETE(g_pPlayerManager);

	// Delete the network manager instance
	SAFE_DELETE(g_pNetworkManager);

	// Delete the net module instance
	SAFE_DELETE(g_pNetModule);

	// Delete the config instance
	SAFE_DELETE(g_pConfig);

	CLogFile::Printf("Server exited");

	// Close the log file
	CLogFile::Close();
}

bool CServer::IsActive()
{
	return m_bActive;
}

void CServer::SetTitle(String strTitle)
{
	SetConsoleTitle(strTitle.C_String());
}

void CServer::OnCloseEvent()
{
	m_bActive = false;
}

void CServer::AddToInputQueue(String strString)
{
	m_inputQueueMutex.Lock();
	m_inputQueue.push(strString);
	m_inputQueueMutex.Unlock();
}

void CServer::ProcessInputQueue()
{
	if(m_inputQueueMutex.TryLock(0))
	{
		if(!m_inputQueue.empty())
		{
			// Process
		}

		m_inputQueueMutex.Unlock();
	}
}
