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

CNetModule *      g_pNetModule = NULL;
CNetworkManager * g_pNetworkManager = NULL;
CPlayerManager *  g_pPlayerManager = NULL;

CServer::CServer()
{
	m_bActive = true;
	m_dwLastFPSUpdateTickCount = 0;
	m_dwFrameCount = 0;
	m_dwFramesPerSecond = 0;
}

CServer::~CServer()
{

}

void CServer::OnLoad()
{
	// Open the log file
	CLogFile::Open("Server.log");

	CLogFile::Printf("Starting up server");

	// Create the net module instance
	g_pNetModule = new CNetModule();

	CLogFile::Printf("Net module instance created");

	// Create the network manager
	g_pNetworkManager = new CNetworkManager();

	CLogFile::Printf("Network manager instance created");

	// Create the player manager
	g_pPlayerManager = new CPlayerManager();

	CLogFile::Printf("Player manager instance created");

	// Start up the network manager
	g_pNetworkManager->Startup(9999, 32);

	CLogFile::Printf("Network manager started up");

	// Set the server title
#ifdef WIN32
	SetTitle(SERVER_TITLE);
#endif

	CLogFile::Printf("Server started");

	CLogFile::Printf("Got InitialData RPC from player %d", 0);

	// Read the data they sent us
	String strName;

	strName.Set("Sam");

	// Add them to the player manager
	g_pPlayerManager->Add(0, strName);
}

void CServer::Process()
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

	// Process the network manager
	g_pNetworkManager->Process();
}

void CServer::OnUnload()
{
	CLogFile::Printf("Server exiting...");

	// Delete the player manager
	SAFE_DELETE(g_pPlayerManager);

	// Delete the network manager
	SAFE_DELETE(g_pNetworkManager);

	// Delete the net module instance
	SAFE_DELETE(g_pNetModule);

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
	// TODO: Use an alternative method
	String strTitleCommand("title %s", strTitle.C_String());
	system(strTitleCommand.C_String());
}
