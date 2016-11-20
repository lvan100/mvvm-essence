#pragma once

#include "Application.h"
using namespace Framework;

#include "../DemoWindow.h"

class DemoApplication : public Application {

	DemoWindow* mainWindow = nullptr;

public:
	virtual void Init() {
		mainWindow = new DemoWindow;
		mainWindow->Show();
	}

	virtual void Uninit() {
		delete mainWindow;
	}

};