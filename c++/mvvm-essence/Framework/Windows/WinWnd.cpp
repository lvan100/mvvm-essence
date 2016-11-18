#include "../Application.h"
using namespace Framework;

#include "WinWnd.h"
#include <Windowsx.h>

#include <map>
using namespace std;

namespace {
	using namespace Framework::Windows;

	static map<HWND, Win32Window*> _WndList;

	const int borderX = GetSystemMetrics(SM_CXFRAME);
	const int borderY = GetSystemMetrics(SM_CYFRAME);
	const int captionY = GetSystemMetrics(SM_CYCAPTION);

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

		Win32Window* window = _WndList[hWnd];

		switch (message)
		{
		case WM_CREATE:
		{
			LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;
			window = (Win32Window*)cs->lpCreateParams;
			_WndList[hWnd] = window;
			window->m_hWnd = hWnd;
		}
		break;
		case WM_NCHITTEST:
		{
			RECT rcWnd;
			GetWindowRect(hWnd, &rcWnd);

			int width = rcWnd.right - rcWnd.left;
			int height = rcWnd.bottom - rcWnd.top;

			int xPos = GET_X_LPARAM(lParam) - rcWnd.left;
			int yPos = GET_Y_LPARAM(lParam) - rcWnd.top;

			if (xPos < borderX) {
				if (yPos < borderY) {
					return HTTOPLEFT;
				} else if (yPos <= height - borderY) {
					return HTLEFT;
				} else {
					return HTBOTTOMLEFT;
				}

			} else if (xPos <= width - borderX) {
				if (yPos < borderY) {
					return HTTOP;
				} else if (yPos <= borderX + captionY) {
					return HTCAPTION;
				} else if (yPos <= height - borderY) {
					return HTCLIENT;
				} else {
					return HTBOTTOM;
				}

			} else {
				if (yPos < borderY) {
					return HTTOPRIGHT;
				} else if (yPos <= height - borderY) {
					return HTRIGHT;
				} else {
					return HTBOTTOMRIGHT;
				}
			}
		}
		break;
		case WM_SIZE:
			window->OnSize();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	WCHAR szWindowClass[] = L"Framework::Win32Window";

	ATOM EnsureRegisterWndClass() {
		static bool wndClassRegistered = false;

		if (!wndClassRegistered) {
			wndClassRegistered = true;

			WNDCLASSEXW wcex;
			wcex.cbSize = sizeof(WNDCLASSEXW);

			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = AfxGetApp()->m_hInstance;
			wcex.hIcon = NULL;
			wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = szWindowClass;
			wcex.hIconSm = NULL;

			return RegisterClassExW(&wcex);

		} else {
			return 0;
		}
	}

	HWND AfxCreateWindow(Win32Window* window, WCHAR* title) {

		EnsureRegisterWndClass();

		static DWORD dwExStyle = WS_EX_LEFT | WS_EX_LTRREADING |
			WS_EX_RIGHTSCROLLBAR | WS_EX_APPWINDOW |
			WS_EX_WINDOWEDGE | WS_EX_LAYERED;

		static DWORD dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
			WS_VISIBLE | WS_CAPTION | WS_MAXIMIZE |
			WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
			WS_THICKFRAME | WS_OVERLAPPED;

		return CreateWindowExW(dwExStyle, szWindowClass, title,
			dwStyle, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr,
			nullptr, AfxGetApp()->m_hInstance, window);
	}

}

namespace Framework {
	namespace Windows {

		Win32Window::Win32Window(WCHAR* title) {
			m_hWnd = AfxCreateWindow(this, title);
		}

		Win32Window::~Win32Window() {
		}

		void Win32Window::Show() {
			ShowWindow(m_hWnd, SW_SHOW);
		}

		void Win32Window::Hide() {
			ShowWindow(m_hWnd, SW_HIDE);
		}

		void Win32Window::UpdateFrame() {

			RECT rcWnd;
			::GetWindowRect(m_hWnd, &rcWnd);

			int width = rcWnd.right - rcWnd.left;
			int height = rcWnd.bottom - rcWnd.top;

			HDC hDC = GetWindowDC(m_hWnd);

			HDC hMemDC = ::CreateCompatibleDC(hDC);
			::SelectObject(hMemDC, m_hMemBitmap);

			Graphics graph(hMemDC);
			graph.SetSmoothingMode(SmoothingModeAntiAlias);

			if (m_Backgnd != nullptr) {
				m_Backgnd->Draw(graph, Rect(0, 0, width, height));
			}

			BLENDFUNCTION blend;
			memset(&blend, 0, sizeof(BLENDFUNCTION));
			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.AlphaFormat = AC_SRC_ALPHA;
			blend.SourceConstantAlpha = 255;

			SIZE size = { width, height };

			POINT ptSrc = { 0, 0 };
			POINT ptDst = { rcWnd.left, rcWnd.top };

			::UpdateLayeredWindow(m_hWnd, hDC, &ptDst, &size, hMemDC,
				&ptSrc, 0, &blend, ULW_ALPHA);

			::DeleteDC(hMemDC);

			::ReleaseDC(m_hWnd, hDC);
		}

		void Win32Window::OnSize() {

			RECT rcWnd;
			::GetWindowRect(m_hWnd, &rcWnd);

			int width = rcWnd.right - rcWnd.left;
			int height = rcWnd.bottom - rcWnd.top;

			if (m_hMemBitmap != nullptr) {
				::DeleteObject(m_hMemBitmap);
			}

			HDC hDC = GetWindowDC(m_hWnd);
			HDC hMemDC = ::CreateCompatibleDC(hDC);

			m_hMemBitmap = ::CreateCompatibleBitmap(hDC, width, height);

			::DeleteDC(hMemDC);
			::ReleaseDC(m_hWnd, hDC);

			::OffsetRect(&rcWnd, -rcWnd.left, -rcWnd.top);

			if (IsMaximized(m_hWnd)) {
				rcWnd.top += 8; // 不知这个值是否固定
			}

			HRGN rgnWnd = CreateRectRgnIndirect(&rcWnd);
			SetWindowRgn(m_hWnd, rgnWnd, FALSE);
			DeleteObject(rgnWnd);

			this->UpdateFrame();
		}

	}
}