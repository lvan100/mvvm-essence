#include "WinApp.h"

#include <Gdiplus.h>
using namespace Gdiplus;

namespace Internal {

	ULONG_PTR m_GdiplusToken;
	ULONG_PTR m_GdiHookToken;

	GdiplusStartupInput m_GdiplusStartupInput;
	GdiplusStartupOutput m_GdiplusStartupOutput;

	void InitGdiplus() {
		GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL);
	}

	void UninitGdiplus() {
		GdiplusShutdown(m_GdiplusToken);
	}

}

namespace Framework {
	namespace Windows {

		WinApp::WinApp() {
			m_hInstance = GetModuleHandle(NULL);
			Internal::InitGdiplus();
		}

		WinApp::~WinApp() {
			Internal::UninitGdiplus();
		}

		int WinApp::Run() {

			Init();

			MSG msg; {
				while (GetMessage(&msg, nullptr, 0, 0)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			int ret = (int)msg.wParam; {
				Uninit();
			} return ret;
		}

	}
}