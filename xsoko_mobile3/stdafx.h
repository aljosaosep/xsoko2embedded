// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")

// NOTE - this value is not strongly correlated to the Windows CE OS version being targeted
#define WINVER _WIN32_WCE

#include <ceconfig.h>
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#define SHELL_AYGSHELL
#endif

#ifdef _CE_DCOM
#define _ATL_APARTMENT_THREADED
#endif

#ifdef SHELL_AYGSHELL
#include <aygshell.h>
#pragma comment(lib, "aygshell.lib") 
#endif // SHELL_AYGSHELL



#include <stdio.h>
#include <tchar.h>

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#ifndef _DEVICE_RESOLUTION_AWARE
#define _DEVICE_RESOLUTION_AWARE
#endif
#endif

#ifdef _DEVICE_RESOLUTION_AWARE
#include "DeviceResolutionAware.h"
#endif

#if _WIN32_WCE < 0x500 && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
	#pragma comment(lib, "ccrtrtti.lib")
	#ifdef _X86_	
		#if defined(_DEBUG)
			#pragma comment(lib, "libcmtx86d.lib")
		#else
			#pragma comment(lib, "libcmtx86.lib")
		#endif
	#endif
#endif

#include <altcecrt.h>

// TODO: reference additional headers your program requires here
#include "vector.h"
#include "camera.h"
#include "object.h"
#include "CommonStructures.h"
#include "messages.h"
#include "renderer/renderer.h"
#include "renderer/texture.h"
//#include "game.h"
#include "input.h"
#include "session.h"
#include "levelbox.h"
#include "core.h"
#include "resource.h"
#include "level.h"
#include "player.h"
#include "game.h"
#include "gui.h"

#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <GLES/glutes.h>
#include <GLES/glues.h>
#include <windows.h>

//#include <afstr.h>
//#include <atlstr.h>



