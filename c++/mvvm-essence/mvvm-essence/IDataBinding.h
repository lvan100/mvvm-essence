#pragma once

namespace mvvm {
	namespace model {

		/**
		 * ��������ģ������
		 */
		template<typename T> class Model;

	}
}

namespace mvvm {
	namespace binding {
		using namespace model;

		/**
		 * ���ݰ󶨵Ķ���
		 */
		template<typename T> struct IDataBinding {

			/**
			 * ˢ��Ŀ������ģ�͵�ֵ
			 */
			virtual void refresh() = 0;
			virtual void set(T&& value) = 0;

			virtual Model<T>* getTarget() = 0;
			virtual void setTarget(Model<T>* target) = 0;

		};

	}
}