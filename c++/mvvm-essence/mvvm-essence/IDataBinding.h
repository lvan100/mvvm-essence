#pragma once

#include "IModel.h"
using namespace mvvm::model;

namespace mvvm {
	namespace binding {

		/**
		 * ���ݰ󶨵Ķ���
		 */
		template<typename T> struct IDataBinding {

			virtual T get() = 0;
			virtual void set(T&& value) = 0;

			virtual IModel<T>* getTarget() = 0;
			virtual void setTarget(IModel<T>* target) = 0;

		};

	}
}