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

// Network version
#define NETWORK_VERSION 0x1

// Debug identifier
#ifdef _DEBUG
#define DEBUG_IDENTIFIER " - Debug"
#else
#define DEBUG_IDENTIFIER
#endif

// Max player limit
#define PLAYER_MAX 32

// Max name length
#define NICK_MAX 32

// Invalid entity id value
#define INVALID_ENTITY_ID 0xFF

// Type used for entity ids
// NOTE: Must be unsigned
typedef unsigned char EntityId;

// Safe object deletion macro
#define SAFE_DELETE(data) if(data) delete data;
