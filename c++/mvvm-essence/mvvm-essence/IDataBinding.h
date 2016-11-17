#pragma once

namespace mvvm {
	namespace model {

		template<typename T> class Model;
		template<typename T> class Property;

	}
}

namespace mvvm {
	namespace binding {
		using namespace model;

		/**
		 * 数据绑定的定义
		 */
		template<typename T> struct IDataBinding {

			/**
			 * 刷新目标属性的值
			 */
			virtual void refresh() = 0;
			virtual void set(T&& value) = 0;

			virtual Property<T>* getTarget() = 0;
			virtual void setTarget(Property<T>* target) = 0;

		};

	}
}