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
		template<typename S, typename T, typename VConv = ValueConverter<S, T>>
		class DataBinding : public IDataBinding<T> {

		private:
			/**
			 * ���ݰ󶨵�Դ����
			 */
			Model<S>* source;

			/**
			 * ���ݰ󶨵�����
			 */
			BindingType type;

			/**
			 * ���ݰ󶨵�Ŀ�����
			 */
			DependencyObject<T>* target;

		private:
			DataBinding(BindingType type, Model<S>* source) {
				this->source = source;
				this->type = type;
			}

			/**
			 * ��ֹʹ��ջ�����ǻ�����ʱ�����緶Χʹ�û�����Ŀ��ǡ�
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