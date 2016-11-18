#include "stdafx.h"

#include "Window.h"
#include "Application.h"
using namespace Framework;

namespace {
	const int borderX = 8;
	const int borderY = 8;
	const int caption = GetSystemMetrics(SM_CYCAPTION);
}

class DemoDrawable : public Drawable {

	virtual void Draw(Graphics& graph, Rect rect) {

		Image image(TEXT("bianping-christmas-2014-02.png"));

		graph.FillRectangle(new Gdiplus::SolidBrush(Gdiplus::Color(200, 214, 219, 233)),
			0, 0, rect.Width, rect.Height);

		graph.FillRectangle(new Gdiplus::SolidBrush(Gdiplus::Color(255, 255, 255, 255)),
			borderX, borderY + caption, rect.Width - borderX * 2, rect.Height - borderY * 2 - caption);

		graph.DrawImage(&image, borderX, borderY + caption, image.GetWidth(), image.GetHeight());

		graph.DrawRectangle(new Pen(Color(13, 32, 45), 0.5f), 0, 0, rect.Width - 1, rect.Height - 1);
	}

};

class DemoApplication : public Application {

	Window* window = nullptr;
	Drawable* bkgnd = nullptr;

public:
	virtual void Init() {

		bkgnd = new DemoDrawable();

		window = new Window(L"ÖÐ¹ú");
		window->m_Backgnd = bkgnd;
		window->Show();
	}

	virtual void Uninit() {
		delete window;
		delete bkgnd;
	}

};

int APIENTRY wWinMain(_In_ HINSTANCE /* hInstance */,
	_In_opt_ HINSTANCE /* hPrevInstance */,
	_In_ LPWSTR    /* lpCmdLine */,
	_In_ int       /* nCmdShow */) {
	return DemoApplication().Run();
}