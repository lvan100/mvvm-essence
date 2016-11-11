#pragma once

#include <memory>
using namespace std;

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
				return (T) value;
			}

			S reverseConvert(T value) {
				return (S) value;
			}

		};

		/**
		 * 数据绑定的实现
		 */
		template<typename S, typename T>
		class DataBinding : public IDataBinding<T> {

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

		private:
			DataBinding(BindingType type, IModel<S>* source) {
				this->source = source;
				this->type = type;
			}

			/**
			 * 禁止使用栈类型是基于临时变量跨范围使用会崩溃的考虑。
			 */

			template<typename S, typename T>
			friend unique_ptr<DataBinding<S, T>>
			make_binding(BindingType type, IModel<S>* source);

		public:
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
				source->addNotifyValueChanged(target);
				this->target = target;
			}

		private:
			/**
			 * 值转换器
			 */
			ValueConverter<S, T> converter = ValueConverter<S, T>();

		public:
			virtual T get() override {
				PrintHelper::Print(this->toString().append(":getValue"));
				return converter.convert(source->get());
			}

			virtual void set(T value) override {
				PrintHelper::EnterPrint(this->toString().append(":setValue.begin"));
				{
					if (getType() == BindingType::TwoWay) {
						source->set(converter.reverseConvert(value));
					}
				}
				PrintHelper::ExitPrint(this->toString().append(":setValue.end"));
			}

		public:
			string toString() {
				stringstream ss;
				ss << "DataBinding@" << this;
				return ss.str();
			}

		};

		template<typename S, typename T>
		inline unique_ptr<DataBinding<S, T>> make_binding(BindingType type, IModel<S>* source) {
			return unique_ptr<DataBinding<S, T>>(new DataBinding<S, T>(type, source));
		}

	}
}