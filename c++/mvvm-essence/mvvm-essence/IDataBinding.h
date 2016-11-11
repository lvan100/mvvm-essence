#pragma once

#include "IModel.h"
using namespace mvvm::model;

namespace mvvm {
	namespace binding {

		/**
		 * 数据绑定的定义
		 */
		template<typename T> struct IDataBinding {

			virtual T get() = 0;
			virtual void set(T&& value) = 0;

			virtual IModel<T>* getTarget() = 0;
			virtual void setTarget(IModel<T>* target) = 0;

		};

	}
}