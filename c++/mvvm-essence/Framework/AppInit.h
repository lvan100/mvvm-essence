#pragma once

namespace Framework {

	class AppInit {

	public:
		virtual void Init() = 0;
		virtual void Uninit() = 0;

	};

}