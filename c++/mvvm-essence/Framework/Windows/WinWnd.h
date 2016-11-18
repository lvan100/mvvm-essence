#pragma once

#include "../Drawable.h"

#include <Windows.h>

namespace Framework {
	namespace Windows {

		class Win32Window {

		public:
			Win32Window(WCHAR* title);
			virtual ~Win32Window();

			void UpdateFrame();

			void Show();
			void Hide();

		public:
			HWND m_hWnd;

		public:
			void OnSize();

		public:
			Drawable* m_Backgnd = nullptr;
			HBITMAP m_hMemBitmap = nullptr;

		};

	}
}