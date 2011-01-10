//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CServer.cpp
// Project: Server
// Author(s): jenksta, mabako
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

#ifdef WIN32
#define SERVER_TITLE MOD_NAME " v" MOD_VERSION_STRING " Server"
#endif

CConfig *          g_pConfig = NULL;
CNetworkManager *  g_pNetworkManager = NULL;
CPlayerManager *   g_pPlayerManager = NULL;
CRootEntity *      g_pRootEntity = NULL;
CResourceManager * g_pResourceManager = NULL;

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

	// Install our exception handler
	CExceptionHandler::Install();

	CLogFile::Printf("Starting up " MOD_NAME " v" MOD_VERSION_STRING " server");

	// Create the config instance
	g_pConfig = new CConfig();

	if(!g_pConfig)
	{
		CLogFile::Printf("Failed to create config instance");
		return false;
	}

	CLogFile::Printf("Config instance created");

	// Open the config file
	if(!g_pConfig->Open(String("%sServer.conf", SharedUtility::GetAppPath())))
		CLogFile::Printf("Failed to open config file, Settings will default to appropriate values.");
	else
		CLogFile::Printf("Config file opened");

	// Initialize the net module
	if(!CNetModule::Init())
	{
		CLogFile::Printf("Failed to initialize the net module");
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
	int iServerPort = GetConfigInteger("port", 9999);

	// Get show fps
	m_bShowFPS = GetConfigBoolean("showfps", true);

	// Start up the network manager
	g_pNetworkManager->Startup(iServerPort, PLAYER_MAX);

	CLogFile::Printf("Network manager started up");

	// Create the resource and scripting manager
	CEntityIDs::Initalize();
	g_pRootEntity = new CRootEntity();
	g_pResourceManager = new CResourceManager();

	// Load resources, get the first resource node
	if(g_pConfig->GetXML()->findNode("resource"))
	{
		while(true)
		{
			// Get the resource name
			String strResource = g_pConfig->GetXML()->nodeContent();

			// Make sure the name is valid and attempt to load the resource
			if(strResource && !strResource.IsEmpty())
				g_pResourceManager->Load(strResource);

			// Attempt to load the next resource node (if any)
			if(!g_pConfig->GetXML()->nextNode())
				break;
		}
	}
	/*TiXmlDocument pDocument("Server.conf");
	if(pDocument.LoadFile())
	{
		TiXmlNode* pNode = pDocument.RootElement()->FirstChild("resource");
		while(pNode)
		{
			String strResource = pNode->ToElement()->GetText();
			
			pNode = pNode->NextSibling("resource");
		}
	}*/

	// Set the server title
#ifdef WIN32
	SetTitle(SERVER_TITLE);
#endif

	CLogFile::Printf("Server started");

	return true;
}

void CServer::Process()
{
	// Get the current tick count
	DWORD dwTickCount = GetTickCount();

	// Is show fps enabled?
	if(m_bShowFPS)
	{
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

	// Process the resource manager
	g_pResourceManager->Process(dwTickCount);

	// Process the input queue
	ProcessInputQueue();
}

void CServer::OnUnload()
{
	CLogFile::Printf("Server exiting...");

	// Delete the resource manager
	SAFE_DELETE(g_pResourceManager);

	// Delete the scripting manager
	SAFE_DELETE(g_pRootEntity);

	// Delete the player manager instance
	SAFE_DELETE(g_pPlayerManager);

	// Delete the network manager instance
	SAFE_DELETE(g_pNetworkManager);

	// Shutdown the net module
	CNetModule::Shutdown();

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
	SetConsoleTitle(strTitle);
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
		while(!m_inputQueue.empty())
		{
			// Get the input string
			String strInput = m_inputQueue.front();

			// Erase the input string from the input queue
			m_inputQueue.pop();

			// Process the input string
			// NOTE: HARDCODED FOR NOW
			// TODO: CServerCommandHandler
			if(!strInput.ICompare("shutdown") || !strInput.ICompare("exit") || !strInput.ICompare("quit"))
			{
				// Shutdown command, set the active flag to false and don't process any more input
				m_bActive = false;
				break;
			}
		}

		m_inputQueueMutex.Unlock();
	}
}

String CServer::GetConfigString(String strKey, String strDefaultValue)
{
	String strValue;

	if(!(g_pConfig && g_pConfig->GetValueAsString(strKey, strDefaultValue, &strValue)))
	{
		CLogFile::Printf("Failed to get '%s' value from config, defaulting to '%s'", strKey.C_String(), strDefaultValue.C_String());
	}

	return strValue;
}

int CServer::GetConfigInteger(String strKey, int iDefaultValue)
{
	int iValue = 0;

	if(!(g_pConfig && g_pConfig->GetValueAsInteger(strKey, iDefaultValue, &iValue)))
	{
		CLogFile::Printf("Failed to get '%s' value from config, defaulting to '%d'", strKey.C_String(), iDefaultValue);
	}

	return iValue;
}

float CServer::GetConfigFloat(String strKey, float fDefaultValue)
{
	float fValue = 0.0f;

	if(!(g_pConfig && g_pConfig->GetValueAsFloat(strKey, fDefaultValue, &fValue)))
	{
		CLogFile::Printf("Failed to get '%s' value from config, defaulting to '%f'", strKey.C_String(), fDefaultValue);
	}

	return fValue;
}

bool CServer::GetConfigBoolean(String strKey, bool bDefaultValue)
{
	bool bValue = false;

	if(!(g_pConfig && g_pConfig->GetValueAsBoolean(strKey, bDefaultValue, &bValue)))
	{
		CLogFile::Printf("Failed to get '%s' value from config, defaulting to '%s'", strKey.C_String(), (bDefaultValue ? "true" : "false"));
	}

	return bValue;
}
