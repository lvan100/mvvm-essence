#pragma once

#include "PrintHelper.h"
#include "IDataBinding.h"

namespace mvvm {
	namespace binding {

		/**
		 * ���ݰ󶨵�����
		 */
		enum BindingType {
			OneWay, TwoWay
		};

		/**
		 * ֵת����
		 */
		template<typename S, typename T> struct ValueConverter {

			T convert(S value) {
				return (T)value;
			}

			S reverseConvert(T value) {
				return (S)value;
			}

		};

		/**
		 * ֵת����
		 */
		template<typename S, typename T> struct ValueConverter<S*, T> {

			T convert(S* value) {
				return (T)(*value);
			}

			S* reverseConvert(T value) {
				return new S((S)value);
			}

		};

		/**
		 * ֵת����
		 */
		template<typename S, typename T> struct ValueConverter<S, T*> {

			T* convert(S value) {
				return new T((T)value);
			}

			S reverseConvert(T* value) {
				return (S)(*value);
			}

		};

		/**
		 * ֵת����
		 */
		template<typename S, typename T> struct ValueConverter<S*, T*> {

			T* convert(S* value) {
				return new T((T)*value);
			}

			S* reverseConvert(T* value) {
				return new S((S)*value);
			}

		};

		/**
		 * ���ݰ󶨵�ʵ��
		 */
		template<typename S, typename T> class DataBinding : public IDataBinding<T> {

		private:
			/**
			 * ���ݰ󶨵�Դ����
			 */
			IModel<S>* source;

			/**
			 * ���ݰ󶨵�Ŀ�����
			 */
			IModel<T>* target;

			/**
			 * ���ݰ󶨵�����
			 */
			BindingType type;

		public:
			DataBinding(BindingType type) {
				this->type = type;
			}

			DataBinding(BindingType type, IModel<S>* source) {
				this->source = source;
				this->type = type;
			}

			BindingType getType() {
				return type;
			}

			void setType(BindingType type) {
				this.type = type;
			}

			IModel<S>* getSource() {
				return source;
			}

			void setSource(IModel<S>* source) {
				this->source = source;
			}

			virtual IModel<T>* getTarget() override {
				return target;
			}

			virtual void setTarget(IModel<T>* target) override {
				this->target = target;
				if (source != nullptr) {
					source->addNotifyValueChanged(target);
				}
			}

		private:
			/**
			 * ֵת����
			 */
			ValueConverter<S, T>* converter = new ValueConverter<S, T>();

		public:
			void setValueConverter(ValueConverter<S, T>* converter) {
				if (converter != nullptr) {
					this->converter = converter;
				}
			}

			virtual T get() override {
				PrintHelper::getInstance()->print(this->toString().append(":getValue"));
				return converter->convert(source->get());
			}

			virtual void set(T value) override {
				PrintHelper::getInstance()->enterPrint(this->toString().append(":setValue.begin"));
				{
					if (getType() == BindingType::TwoWay) {
						source->set(converter->reverseConvert(value));
					}
				}
				PrintHelper::getInstance()->exitPrint(this->toString().append(":setValue.end"));
			}

		public:
			string toString() {
				stringstream ss;
				ss << "DataBinding@" << this;
				return ss.str();
			}

		};

	}
}