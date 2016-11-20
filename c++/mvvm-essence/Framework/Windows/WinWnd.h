#pragma once

#include "../Drawable.h"

#include <Windows.h>

namespace Framework {
	namespace Windows {

		class Win32Window {

		public:
			Win32Window();
			virtual ~Win32Window();

			void UpdateFrame();

			void Show();
			void Hide();

		public:
			HWND m_hWnd;

		public:
			void OnSize();

		public:
			Drawable* m_DefaultBackgnd;
			Drawable* m_Backgnd = nullptr;

			HBITMAP m_hMemBitmap = nullptr;

		};

	}
}