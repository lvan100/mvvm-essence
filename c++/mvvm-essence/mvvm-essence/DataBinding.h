#pragma once

#include <memory>
#include <type_traits>
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

			void convert(const S& source, T& target) {
				target = (T)source;
			}

			S reverseConvert(T&& value) {
				return move(S(move(value)));
			}

		};

		template<typename S, typename T>
		class BaseBinding : public IDataBinding<T> {

		protected:
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

		protected:
			BaseBinding(BindingType type, IModel<S>* source) {
				this->source = source;
				this->type = type;
			}

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

		public:
			string toString() const {
				stringstream ss;
				ss << "DataBinding@" << this;
				return ss.str();
			}

		};

		/**
		 * 数据绑定的实现
		 */
		template<typename S, typename T, bool Convertible>
		class DataBinding {
		};

		/**
		 * 数据绑定的实现
		 */
		template<typename S, typename T>
		class DataBinding<S, T, true> : public BaseBinding<S, T> {

		protected:
			DataBinding(BindingType type, IModel<S>* source)
				: BaseBinding(type, source) {
			}

			/**
			 * 禁止使用栈类型是基于临时变量跨范围使用会崩溃的考虑。
			 */

			template<typename S, typename T, bool Convertible = true>
			friend unique_ptr<DataBinding<S, T, Convertible>>
			make_binding(BindingType type, IModel<S>* source);

		public:
			virtual void refresh() override {
				PrintHelper::Print(this->toString().append(":refresh"));
				const_cast<T&>(target->get()) = T(source->get());
			}

			virtual void set(T&& value) override {
				PrintHelper::EnterPrint(this->toString().append(":setValue.begin"));
				{
					if (getType() == BindingType::TwoWay) {
						source->set(move(S(move(value))));
					}
				}
				PrintHelper::ExitPrint(this->toString().append(":setValue.end"));
			}

		};

		/**
		 * 数据绑定的实现
		 */
		template<typename S, typename T>
		class DataBinding<S, T, false> : public BaseBinding<S, T> {

		protected:
			DataBinding(BindingType type, IModel<S>* source)
				: BaseBinding(type, source) {
			}

			/**
			 * 禁止使用栈类型是基于临时变量跨范围使用会崩溃的考虑。
			 */

			template<typename S, typename T, bool Convertible = false>
			friend unique_ptr<DataBinding<S, T, Convertible>>
			make_binding(BindingType type, IModel<S>* source);

		private:
			/**
			 * 值转换器
			 */
			ValueConverter<S, T> converter = ValueConverter<S, T>();

		public:
			virtual void refresh() override {
				PrintHelper::Print(this->toString().append(":refresh"));
				return converter.convert(source->get(), const_cast<T&>(target->get()));
			}

			virtual void set(T&& value) override {
				PrintHelper::EnterPrint(this->toString().append(":setValue.begin"));
				{
					if (getType() == BindingType::TwoWay) {
						source->set(move(converter.reverseConvert(move(value))));
					}
				}
				PrintHelper::ExitPrint(this->toString().append(":setValue.end"));
			}

		};

		template<typename S, typename T, bool Convertible = is_convertible<S, T>::value && is_convertible<T, S>::value>
		inline unique_ptr<DataBinding<S, T, Convertible>> make_binding(BindingType type, IModel<S>* source) {
			return unique_ptr<DataBinding<S, T, Convertible>>(new DataBinding<S, T, Convertible>(type, source));
		}

	}
}