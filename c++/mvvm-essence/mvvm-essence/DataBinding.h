#pragma once

#include <memory>
using namespace std;

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

			static void convert(const S& source, T& target) {
				target = (T)source;
			}

			static S reverseConvert(T&& value) {
				return move(S(move(value)));
			}

		};

		/**
		 * ���ݰ󶨵�ʵ��
		 */
		template<typename S, typename T>
		class DataBinding : public IDataBinding<T> {

		private:
			/**
			 * ���ݰ󶨵�Դ����
			 */
			Model<S>* source;

			/**
			 * ���ݰ󶨵�Ŀ�����
			 */
			Model<T>* target;

			/**
			 * ���ݰ󶨵�����
			 */
			BindingType type;

		private:
			DataBinding(BindingType type, Model<S>* source) {
				this->source = source;
				this->type = type;
			}

			/**
			 * ��ֹʹ��ջ�����ǻ�����ʱ�����緶Χʹ�û�����Ŀ��ǡ�
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