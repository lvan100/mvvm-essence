#pragma once

#ifdef WIN32
#include "Windows/WinDrawable.h"
#endif

namespace Framework {

#ifdef WIN32
	using Drawable = Windows::WinDrawable;
#endif

}