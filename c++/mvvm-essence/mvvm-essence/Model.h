#pragma once

#include <memory>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

#include "PrintHelper.h"

#include "IDataBinding.h"
using namespace mvvm::binding;

namespace mvvm {
	namespace model {

		/**
		 * 基础数据模型的实现
		 */
		template<typename T> class Model : public IModel<T> {

		private:
			/**
			 * 数据值
			 */
			T _value;

			/**
			 * 是否只读
			 */
			bool _readOnly = false;

			/**
			 * 数据绑定对象
			 */
			unique_ptr<IDataBinding<T>> dataBinding;

		public:
			// 要求数据类型支持拷贝运算符
			Model(T value) : _value(value) {}
			Model(T value, bool readOnly) : _value(value), _readOnly(readOnly) {}

			virtual T get() override {
				PrintHelper::Print(this->toString().append(":Model.getValue"));
				if (dataBinding.get() == nullptr) {
					return _value;
				} else {
					return dataBinding->get();
				}
			}

			virtual void set(T value) override {
				PrintHelper::EnterPrint(this->toString().append(":Model.setValue.begin"));

				if (!readOnly()) {
					if (dataBinding.get() == nullptr) {

						stringstream ss_oldValue;
						ss_oldValue << _value;

						stringstream ss_newValue;
						ss_newValue << value;

						PrintHelper::EnterPrint(this->toString().append(":Model.setValue=")
							.append(ss_oldValue.str()).append("->").append(ss_newValue.str()));

						PrintHelper::Exit();

						// 要求数据类型支持=及!=操作符
						if (this->_value != value) {
							this->_value = value;

							PrintHelper::EnterPrint(this->toString()
								.append(":Model.notifyValueChanged.begin"));
							{
								notifyValueChanged();
							}
							PrintHelper::ExitPrint(this->toString()
								.append(":Model.notifyValueChanged.end"));
						}

					} else {
						dataBinding->set(value);
					}
				}

				PrintHelper::ExitPrint(this->toString().append(":Model.setValue.end"));
			}

			bool readOnly() {
				return _readOnly;
			}

			void setReadOnly(bool readOnly) {
				this->_readOnly = readOnly;
			}

			unique_ptr<IDataBinding<T>>& getDataBinding() {
				return dataBinding;
			}

			void setDataBinding(unique_ptr<IDataBinding<T>> dataBinding) {
				PrintHelper::EnterPrint(this->toString()
					.append(":Model.setDataBinding.begin"));
				{
					this->dataBinding.reset(dataBinding.release());
					this->dataBinding->setTarget(this);

					this->notifyValueChanged();
				}
				PrintHelper::ExitPrint(this->toString()
					.append(":Model.setDataBinding.end"));
			}

		private:
			/**
			 * 值变化通知列表
			 */
			vector<INotifyValueChanged*> notifyList;

		public:
			virtual void removeNotifyValueChanged(INotifyValueChanged* notify) {

				auto iter = find_if(notifyList.begin(), notifyList.end(),
					[&](INotifyValueChanged* p) {
					return p == notify;
				});

				if (iter != notifyList.end()) {
					notifyList.erase(iter);
				}
			}

			virtual void addNotifyValueChanged(INotifyValueChanged* notify) {
				notifyList.push_back(notify);
			}

			virtual void onValueChanged(void* model) override {
				PrintHelper::EnterPrint(this->toString()
					.append(":Model.onValueChanged"));

				PrintHelper::Print(this->toString()
					.append(":Model.notifyValueChanged.begin"));
				{
					notifyValueChanged();
				}
				PrintHelper::ExitPrint(this->toString()
					.append(":Model.notifyValueChanged.end"));
			}

		public:
			void notifyValueChanged() {
				for (INotifyValueChanged* notify : notifyList) {
					PrintHelper::EnterPrint(":Notify.onValueChanged.begin");
					{
						notify->onValueChanged(this);
					}
					PrintHelper::ExitPrint(":Notify.onValueChanged.end");
				}
			}

			string toString() {
				stringstream ss;
				ss << "Model@" << this;
				return ss.str();
			}

		};

		/**
		 * 针对指针特化的数据模型的实现
		 */
		template<typename T> class Model<T*> {

			// 我认为不应该实现对指针的数据模型

		};

		/**
		 * 针对引用特化的数据模型的实现
		 */
		template<typename T> class Model<T&> {

			// 我认为不应该实现对引用的数据模型

		};

	}
}