#pragma once

#include "../AppInit.h"

#include <Windows.h>

namespace Framework {
	namespace Windows {

		class WinApp : public AppInit {

		public:
			WinApp();

			int Run();

		public:
			virtual ~WinApp();

		public:
			HINSTANCE m_hInstance;

		};

	}
}