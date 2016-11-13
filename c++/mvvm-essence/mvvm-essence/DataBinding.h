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

			static void convert(const S& source, T& target) {
				target = (T)source;
			}

			static S reverseConvert(T&& value) {
				return move(S(move(value)));
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
			Model<S>* source;

			/**
			 * 数据绑定的目标对象
			 */
			Model<T>* target;

			/**
			 * 数据绑定的类型
			 */
			BindingType type;

		private:
			DataBinding(BindingType type, Model<S>* source) {
				this->source = source;
				this->type = type;
			}

			/**
			 * 禁止使用栈类型是基于临时变量跨范围使用会崩溃的考虑。
			 */

			template<typename S, typename T>
			friend unique_ptr<DataBinding<S, T>>
			make_binding(BindingType type, Model<S>* source);

		public:
			BindingType getType() {
				return type;
			}

			void setType(BindingType type) {
				this.type = type;
			}

			Model<S>* getSource() {
				return source;
			}

			void setSource(Model<S>* source) {
				this->source = source;
			}

			virtual Model<T>* getTarget() override {
				return target;
			}

			virtual void setTarget(Model<T>* target) override {
				source->addNotifyValueChanged(target);
				this->target = target;
			}

		public:
			virtual void refresh() override {
				PrintHelper::Print(this->toString().append(":refresh"));
				return ValueConverter<S, T>::convert(source->get(), const_cast<T&>(target->get()));
			}

			virtual void set(T&& value) override {
				PrintHelper::EnterPrint(this->toString().append(":setValue.begin"));
				{
					if (getType() == BindingType::TwoWay) {
						source->set(move(ValueConverter<S, T>::reverseConvert(move(value))));
					}
				}
				PrintHelper::ExitPrint(this->toString().append(":setValue.end"));
			}

		public:
			string toString() const {
				stringstream ss;
				ss << "DataBinding@" << this;
				return ss.str();
			}

		};

		template<typename S, typename T>
		inline unique_ptr<DataBinding<S, T>> make_binding(BindingType type, Model<S>* source) {
			return unique_ptr<DataBinding<S, T>>(new DataBinding<S, T>(type, source));
		}

	}
}