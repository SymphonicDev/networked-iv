//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: Common.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

// Mod name
#define MOD_NAME "Networked: IV"

// Mod debug version
#ifdef _DEBUG
#define MOD_VER_DBG "-debug"
#else
#define MOD_VER_DBG
#endif

// Mod version string
#define MOD_VERSION_STRING "1.0-pre-alpha-1" MOD_VER_DBG

// Network module version
#define NETWORK_MODULE_VERSION 0x1

// Network version
#define NETWORK_VERSION 0x1

// Max player limit
#define PLAYER_MAX 32

// Max name length
#define NICK_MAX 32

// Type used for entity ids
// NOTE: Must be unsigned
typedef unsigned char EntityId;

// Invalid entity id value
#define INVALID_ENTITY_ID 0xFF

// brandnew and sexy: Element ID
typedef unsigned short EntityID;
#define MAX_ENTITIES           0xFFFE
#define INVALID_ENTITY_ID_LONG 0xFFFF

// Safe object deletion macro
#define SAFE_DELETE(data) if(data) { delete data; data = 0; }
