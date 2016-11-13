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

		protected:
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
			// 要求数据类型支持拷贝、移动运算符
			Model(T&& value) : _value(move(value)) {}
			Model(T&& value, bool readOnly) : _value(move(value)), _readOnly(readOnly) {}

			virtual const T& get() const override {
				PrintHelper::Print(this->toString().append(":Model.getValue"));
				return _value;
			}

			virtual void set(T&& value) override {
				PrintHelper::EnterPrint(this->toString().append(":Model.setValue.begin"));

				if (!readOnly()) {
					if (dataBinding.get() == nullptr) {

						stringstream ss_oldValue;
						ss_oldValue << _value;

						stringstream ss_newValue;
						ss_newValue << value;

						PrintHelper::EnterPrint(this->toString().append(":Model.setValue=")
							.append(ss_oldValue.str()).append("->").append(ss_newValue.str()));

						// 要求数据类型支持!=操作符
						if (this->_value != value) {

							// 要求数据类型支持=操作符
							this->_value = move(value);

							PrintHelper::Exit();

							notifyValueChanged();

						} else {
							PrintHelper::Exit();
						}

					} else {
						dataBinding->set(move(value));
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

			void setDataBinding(unique_ptr<IDataBinding<T>> binding) {
				PrintHelper::EnterPrint(this->toString()
					.append(":Model.setDataBinding.begin"));
				{
					dataBinding.reset(binding.release());
					dataBinding->setTarget(this);

					this->refreshData();
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
					[&notify](INotifyValueChanged* p) {
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
					.append(":Model.onValueChanged.begin"));

				this->refreshData();

				PrintHelper::ExitPrint(this->toString()
					.append(":Model.onValueChanged.end"));
			}

		private:
			void refreshData() {
				PrintHelper::EnterPrint(this->toString()
					.append(":Model.refreshData.begin"));
				{
					PrintHelper::Enter();
					{
						dataBinding->refresh();

						stringstream ss_value;
						ss_value << _value;

						PrintHelper::Print(this->toString()
							.append(":refreshValue=")
							.append(ss_value.str()));
					}
					PrintHelper::Exit();
				}
				PrintHelper::ExitPrint(this->toString()
					.append(":Model.refreshData.end"));

				notifyValueChanged();
			}

		public:
			void notifyValueChanged() {
				PrintHelper::EnterPrint(this->toString()
					.append(":Model.notifyValueChanged.begin"));
				{
					for (INotifyValueChanged* notify : notifyList) {
						PrintHelper::EnterPrint(":Notify.onValueChanged.begin");
						{
							notify->onValueChanged(this);
						}
						PrintHelper::ExitPrint(":Notify.onValueChanged.end");
					}
				}
				PrintHelper::ExitPrint(this->toString()
					.append(":Model.notifyValueChanged.end"));
			}

			string toString() const {
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

		/**
		 * 集合数据模型的实现
		 */
		template<typename T> class VectorModel : public Model<vector<T>> {

		public:
			// 要求数据类型支持拷贝、移动运算符
			VectorModel(vector<T>&& value) : Model(move(value)) {}
			VectorModel(vector<T>&& value, bool readOnly) : Model(move(value)，readOnly) {}

			VectorModel& operator=(vector<T>&& _Right) {
				PrintHelper::Print(this->toString()
					.append(":VectorModel.operator=.begin"));
				{
					set(move(_Right));
				}
				PrintHelper::Print(this->toString()
					.append(":VectorModel.operator=.end"));

				return *this;
			}

			/**
			 * 只允许对源Model数据进行此操作
			 */
			void push_back(T&& _Val) {
				PrintHelper::Print(this->toString()
					.append(":VectorModel.push_back.begin"));
				{
					if (!readOnly()) {
						if (dataBinding.get() == nullptr) {

							_value.push_back(move(_Val));

							notifyValueChanged();

						} else {
							#if _ITERATOR_DEBUG_LEVEL == 2
								_DEBUG_ERROR("not allowed to push value to binded model");
							#endif /* _ITERATOR_DEBUG_LEVEL == 2 */
						}
					}
				}
				PrintHelper::Print(this->toString()
					.append(":VectorModel.push_back.end"));
			}

			/**
			 * 只允许对源Model数据进行此操作
			 */
			typename vector<T>::iterator
			insert(typename vector<T>::const_iterator _Where, T&& _Val) {
				vector<T>::iterator ret = _value.end();

				PrintHelper::Print(this->toString()
					.append(":VectorModel.insert.begin"));
				{
					if (!readOnly()) {
						if (dataBinding.get() == nullptr) {

							ret = _value.insert(_Where, move(_Val));

							notifyValueChanged();

						} else {
							#if _ITERATOR_DEBUG_LEVEL == 2
								_DEBUG_ERROR("not allowed to insert value to binded model");
							#endif /* _ITERATOR_DEBUG_LEVEL == 2 */
						}
					}
				}
				PrintHelper::Print(this->toString()
					.append(":VectorModel.insert.end"));

				return ret;
			}

			string toString() const {
				stringstream ss;
				ss << "VectorModel@" << this;
				return ss.str();
			}

		};

	}
}