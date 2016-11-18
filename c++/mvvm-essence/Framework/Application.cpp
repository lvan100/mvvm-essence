#include "Application.h"

#include <assert.h>

namespace Framework {

	/**
	 * 全局唯一的应用程序示例
	 */
	Application* _application = nullptr;

	Application::Application() {
		if (_application != nullptr) {
			assert(false);
		}
		_application = this;
	}

	Application::~Application() {

	}

	Application* AfxGetApp() {
		return _application;
	}

}