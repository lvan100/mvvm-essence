#pragma once

#include <memory>
#include <sstream>
#include <algorithm>
using namespace std;

#include "Observable.h"
#include "PrintHelper.h"
#include "IDataBinding.h"

namespace mvvm {
	namespace model {
		using namespace binding;

		/**
		 * 每个依赖对象都有自己的数据拷贝，当底层数据发生变化时，立即刷新
		 * 数据并缓存起来，这样在后续的使用过程中如果底层数据没有发生变化，
		 * 而需要多次获取模型的值时效率更高，因为不用每次都要执行一遍转换。
		 */

		/**
		 * 数据模型的实现
		 */
		template<typename T> class Model : public BaseObservable<INotifyPropertyChanged> {

		protected:
			/**
			 * 数据值
			 */
			T _value;

			/**
			 * 是否只读
			 */
			bool _readOnly = false;
			
		public:
			// 要求数据类型支持拷贝、移动运算符
			Model(T&& value) : _value(move(value)) {}
			Model(T&& value, bool readOnly) : _value(move(value)), _readOnly(readOnly) {}

			bool readOnly() {
				return _readOnly;
			}

			void setReadOnly(bool readOnly) {
				this->_readOnly = readOnly;
			}

			/**
			 * 返回数据模型值的引用，但是又要限制值不能被修改
			 */
			const T& get() const {
				PrintHelper::Print(this->toString().append(":Model.getValue"));
				return _value;
			}

			virtual void set(T&& value) {
				PrintHelper::EnterPrint(this->toString().append(":Model.setValue.begin"));
				{
					if (!readOnly()) {

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

							notifyPropertyChanged(this, 0, nullptr);

						} else {
							PrintHelper::Exit();
						}
					}
				}
				PrintHelper::ExitPrint(this->toString().append(":Model.setValue.end"));
			}

		public:
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
		 * 依赖对象的实现
		 */
		template<typename T> class DependencyObject
			: public Model<T> /* 必须首位继承 */
			, public INotifyPropertyChanged {

		protected:
			/**
			 * 数据绑定对象
			 */
			unique_ptr<IDataBinding<T>> dataBinding;

		public:
			// 要求数据类型支持拷贝、移动运算符
			DependencyObject(T&& value) : Model(move(value)) {}
			DependencyObject(T&& value, bool readOnly) : Model(move(value), readOnly) {}

			virtual void set(T&& value) {
				PrintHelper::EnterPrint(this->toString().append(":DependencyObject.setValue.begin"));
				{
					if (!readOnly()) {
						if (dataBinding.get() != nullptr) {
							dataBinding->set(move(value));
						} else {
							Model::set(move(value));
						}
					}
				}
				PrintHelper::ExitPrint(this->toString().append(":DependencyObject.setValue.end"));
			}

			unique_ptr<IDataBinding<T>>& getDataBinding() {
				return dataBinding;
			}

			void setDataBinding(unique_ptr<IDataBinding<T>> binding) {
				PrintHelper::EnterPrint(this->toString()
					.append(":DependencyObject.setDataBinding.begin"));
				{
					dataBinding.reset(binding.release());
					dataBinding->setTarget(this);

					this->refreshData();
				}
				PrintHelper::ExitPrint(this->toString()
					.append(":DependencyObject.setDataBinding.end"));
			}

			virtual void onPropertyChanged(void* model, int id, void* arg) override {
				PrintHelper::EnterPrint(this->toString()
					.append(":DependencyObject.onPropertyChanged.begin"));

				this->refreshData();

				PrintHelper::ExitPrint(this->toString()
					.append(":DependencyObject.onPropertyChanged.end"));
			}

		private:
			void refreshData() {
				PrintHelper::EnterPrint(this->toString()
					.append(":DependencyObject.refreshData.begin"));
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
					.append(":DependencyObject.refreshData.end"));

				notifyPropertyChanged(this, 0, nullptr);
			}

		public:
			string toString() const {
				stringstream ss;
				ss << "DependencyObject@" << this;
				return ss.str();
			}

		};

		/**
		 * 针对指针特化的依赖对象的实现
		 */
		template<typename T> class DependencyObject<T*> {

			// 我认为不应该实现对指针的依赖对象

		};

		/**
		 * 针对引用特化的依赖对象的实现
		 */
		template<typename T> class DependencyObject<T&> {

			// 我认为不应该实现对引用的依赖对象

		};

		/**
		 * 集合数据模型的实现
		 */
		template<typename T> class VectorModel : public DependencyObject<vector<T>> {

		public:
			// 要求数据类型支持拷贝、移动运算符
			VectorModel(vector<T>&& value) : DependencyObject(move(value)) {}
			VectorModel(vector<T>&& value, bool readOnly) : DependencyObject(move(value)，readOnly) {}

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

							notifyPropertyChanged(this, 0, nullptr);

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

							notifyPropertyChanged(this, 0, nullptr);

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