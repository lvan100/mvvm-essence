#pragma once

namespace mvvm {
	namespace model {

		/**
		 * 每个数据模型都有自己的数据拷贝，当底层数据发生变化时，立即刷新
		 * 数据并缓存起来，这样在后续的使用过程中如果底层数据没有发生变化，
		 * 而需要多次获取模型的值时效率更高，因为不用每次都要执行一遍转换。
		 */

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

			virtual const T& get() const = 0;
			virtual void set(T&& value) = 0;

			virtual void addNotifyValueChanged(INotifyValueChanged* notify) = 0;
			virtual void removeNotifyValueChanged(INotifyValueChanged* notify) = 0;

		};

	}
}