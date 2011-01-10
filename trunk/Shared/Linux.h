//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: Linux.h
// Project: Shared
// Author(s): MaVe
// License: See LICENSE in root directory
//
//==========================================================================

#pragma once

#ifndef WIN32

#include <unistd.h>
#include <limits.h>
#include <dlfcn.h>

#define MAX_PATH PATH_MAX
#define Sleep(ms) usleep((ms) * 1000)
#define ExitProcess(code) _exit(code)

#endif
