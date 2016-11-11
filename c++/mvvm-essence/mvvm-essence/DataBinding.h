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

			T convert(S value) {
				return (T) value;
			}

			S reverseConvert(T value) {
				return (S) value;
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
			IModel<S>* source;

			/**
			 * ���ݰ󶨵�Ŀ�����
			 */
			IModel<T>* target;

			/**
			 * ���ݰ󶨵�����
			 */
			BindingType type;

		private:
			DataBinding(BindingType type, IModel<S>* source) {
				this->source = source;
				this->type = type;
			}

			/**
			 * ��ֹʹ��ջ�����ǻ�����ʱ�����緶Χʹ�û�����Ŀ��ǡ�
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
			 * ֵת����
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