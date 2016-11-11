#pragma once

namespace mvvm {
	namespace model {

		/**
		 * ����ģ��ֵ�仯֪ͨ�ӿ�
		 */
		struct INotifyValueChanged {
			virtual void onValueChanged(void* model) = 0;
		};

		/**
		 * ��������ģ�͵Ķ���
		 */
		template<typename T> struct IModel : public INotifyValueChanged {

			virtual T get() = 0;
			virtual void set(T&& value) = 0;

			virtual void addNotifyValueChanged(INotifyValueChanged* notify) = 0;
			virtual void removeNotifyValueChanged(INotifyValueChanged* notify) = 0;

		};

	}
}