#pragma once

#ifdef WIN32
#include "Windows/WinApp.h"
#endif

namespace Framework {

#ifdef WIN32
	typedef Windows::WinApp BaseApp;
#endif

	class Application : public BaseApp {

	public:
		Application();
		virtual ~Application();

	};

	extern Application* AfxGetApp();

}