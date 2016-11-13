#pragma once

namespace mvvm {
	namespace model {

		/**
		 * 声明数据模型类型
		 */
		template<typename T> class Model;

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
			 * 刷新目标数据模型的值
			 */
			virtual void refresh() = 0;
			virtual void set(T&& value) = 0;

			virtual Model<T>* getTarget() = 0;
			virtual void setTarget(Model<T>* target) = 0;

		};

	}
}