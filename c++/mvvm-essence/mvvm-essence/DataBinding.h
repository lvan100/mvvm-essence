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
		template<typename S, typename T, typename VConv = ValueConverter<S, T>>
		class DataBinding : public IDataBinding<T> {

		private:
			/**
			 * 数据绑定的源对象
			 */
			Model<S>* source;

			/**
			 * 数据绑定的类型
			 */
			BindingType type;

			/**
			 * 数据绑定的目标对象
			 */
			DependencyObject<T>* target;

		private:
			DataBinding(BindingType type, Model<S>* source) {
				this->source = source;
				this->type = type;
			}

			/**
			 * 禁止使用栈类型是基于临时变量跨范围使用会崩溃的考虑。
			 */

			template<typename S, typename T, typename VConv >
			friend void make_binding(Model<S>* source, DependencyObject<T>* target, BindingType type);

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

			virtual DependencyObject<T>* getTarget() override {
				return target;
			}

			virtual void setTarget(DependencyObject<T>* target) override {
				source->addObserver(target);
				this->target = target;
			}

		public:
			virtual void refresh() override {
				PrintHelper::Print(this->toString().append(":refresh"));
				return VConv::convert(source->get(), const_cast<T&>(target->get()));
			}

			virtual void set(T&& value) override {
				PrintHelper::EnterPrint(this->toString().append(":setValue.begin"));
				{
					if (getType() == BindingType::TwoWay) {
						source->set(move(VConv::reverseConvert(move(value))));
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

		template<typename S, typename T, typename VConv = ValueConverter<S, T>>
		inline void make_binding(Model<S>* source, DependencyObject<T>* target, BindingType type) {
			DataBinding<S, T, VConv>* ptr = new DataBinding<S, T, VConv>(type, source);
			target->setDataBinding(unique_ptr<DataBinding<S, T, VConv>>(ptr));
		}

	}
}