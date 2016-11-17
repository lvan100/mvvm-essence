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
		 * ���ݰ󶨵Ķ���
		 */
		template<typename T> struct IDataBinding {

			/**
			 * ˢ��Ŀ�����Ե�ֵ
			 */
			virtual void refresh() = 0;
			virtual void set(T&& value) = 0;

			virtual Property<T>* getTarget() = 0;
			virtual void setTarget(Property<T>* target) = 0;

		};

	}
}