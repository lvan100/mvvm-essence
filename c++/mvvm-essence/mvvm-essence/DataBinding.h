#pragma once

#include "PrintHelper.h"
#include "IDataBinding.h"

namespace mvvm {
	namespace binding {

		/**
		 * 数据绑定的类型
		 */
		enum BindingType {
			OneWay, TwoWay
		};

		/**
		 * 值转换器
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
		 * 值转换器
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
		 * 值转换器
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
		 * 值转换器
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
		 * 数据绑定的实现
		 */
		template<typename S, typename T> class DataBinding : public IDataBinding<T> {

		private:
			/**
			 * 数据绑定的源对象
			 */
			IModel<S>* source;

			/**
			 * 数据绑定的目标对象
			 */
			IModel<T>* target;

			/**
			 * 数据绑定的类型
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
			 * 值转换器
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