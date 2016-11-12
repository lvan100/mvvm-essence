#pragma once

namespace mvvm {
	namespace model {

		/**
		 * ÿ������ģ�Ͷ����Լ������ݿ��������ײ����ݷ����仯ʱ������ˢ��
		 * ���ݲ����������������ں�����ʹ�ù���������ײ�����û�з����仯��
		 * ����Ҫ��λ�ȡģ�͵�ֵʱЧ�ʸ��ߣ���Ϊ����ÿ�ζ�Ҫִ��һ��ת����
		 */

		/**
		 * ����ģ��ֵ�仯֪ͨ�ӿ�
		 */
		struct INotifyValueChanged {

			/**
			 * ֪ͨ����ģ���Ѿ������仯
			 *
			 * @param mode �����仯������ģ��
			 */
			virtual void onValueChanged(void* model) = 0;

		};

		/**
		 * ��������ģ�͵Ķ���
		 */
		template<typename T> struct IModel : public INotifyValueChanged {

			/**
			 * ��������ģ��ֵ�����ã�������Ҫ����ֵ���ܱ��޸�
			 */
			virtual const T& get() const = 0;
			virtual void set(T&& value) = 0;

			virtual void addNotifyValueChanged(INotifyValueChanged* notify) = 0;
			virtual void removeNotifyValueChanged(INotifyValueChanged* notify) = 0;

		};

	}
}