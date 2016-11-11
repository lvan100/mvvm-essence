#pragma once

namespace mvvm {
	namespace model {

		/**
		 * 数据模型值变化通知接口
		 */
		struct INotifyValueChanged {
			virtual void onValueChanged(void* model) = 0;
		};

		/**
		 * 基础数据模型的定义
		 */
		template<typename T> struct IModel : public INotifyValueChanged {

			virtual T get() = 0;
			virtual void set(T&& value) = 0;

			virtual void addNotifyValueChanged(INotifyValueChanged* notify) = 0;
			virtual void removeNotifyValueChanged(INotifyValueChanged* notify) = 0;

		};

	}
}