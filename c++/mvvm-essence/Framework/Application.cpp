#include "Application.h"

#include <assert.h>

namespace Framework {

	/**
	 * ȫ��Ψһ��Ӧ�ó���ʾ��
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