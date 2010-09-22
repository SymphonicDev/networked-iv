//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: RPCIdentifiers.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#include <StdInc.h>

enum eRPCIdentfiers
{
	// Request/send initial client data
	RPC_INITIAL_DATA,

	// Add a player
	RPC_ADD_PLAYER,

	// Delete a player
	RPC_DELETE_PLAYER,

	// Spawn a player
	RPC_SPAWN_PLAYER,

	// Destroy a player
	RPC_DESTROY_PLAYER,

	// Send chat input
	RPC_CHAT_INPUT
};
