#pragma once

#ifdef WIN32
#include "Windows/WinWnd.h"
#endif

namespace Framework {

#ifdef WIN32
	using Window = Windows::Win32Window;
#endif

}