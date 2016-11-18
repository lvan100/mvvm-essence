#pragma once

#include <Windows.h>

#include <gdiplus.h>
using namespace Gdiplus;

namespace Framework {
	namespace Windows {

		class WinDrawable {

		public:
			virtual ~WinDrawable();

			virtual void Draw(Graphics& graph, Rect rect) = 0;

		};

	}
}