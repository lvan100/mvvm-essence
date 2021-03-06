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
		 * 每个属性都有自己的数据拷贝，当底层数据发生变化时，立即刷新数据
		 * 并缓存起来，这样在后续的使用过程中如果底层数据没有发生变化，而
		 * 需要多次获取模型的值时效率更高，因为不用每次都要执行一遍转换。
		 */

		/**
		 * 当属性的数据将要发生变化但变化不是由底层数据引起时，首先更新属
		 * 性的本地数据，然后再决定是否需要将变化传递给绑定的模型或属性。
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

		public:
			// 要求数据类型支持拷贝、移动运算符
			Model(T&& value) : _value(move(value)) {}

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
		 * 属性的实现
		 */
		template<typename T> class Property
			: public Model<T> /* 必须首位继承 */
			, public INotifyPropertyChanged {

		protected:
			/**
			 * 数据绑定对象
			 */
			unique_ptr<IDataBinding<T>> dataBinding;

		public:
			// 要求数据类型支持拷贝、移动运算符
			Property(T&& value) : Model(move(value)) {}

			virtual void set(T&& value) {
				PrintHelper::EnterPrint(this->toString().append(":Property.setValue.begin"));
				{
					// 首先更新本地数据
					T newValue = value;
					Model::set(move(newValue));

					if (dataBinding.get() != nullptr) {
						dataBinding->set(move(value));
					}
				}
				PrintHelper::ExitPrint(this->toString().append(":Property.setValue.end"));
			}

			unique_ptr<IDataBinding<T>>& getDataBinding() {
				return dataBinding;
			}

			void setDataBinding(unique_ptr<IDataBinding<T>> binding) {
				PrintHelper::EnterPrint(this->toString()
					.append(":Property.setDataBinding.begin"));
				{
					dataBinding.reset(binding.release());
					dataBinding->setTarget(this);

					this->refreshData();
				}
				PrintHelper::ExitPrint(this->toString()
					.append(":Property.setDataBinding.end"));
			}

			virtual void onPropertyChanged(void* model, int id, void* arg) override {
				PrintHelper::EnterPrint(this->toString()
					.append(":Property.onPropertyChanged.begin"));

				this->refreshData();

				PrintHelper::ExitPrint(this->toString()
					.append(":Property.onPropertyChanged.end"));
			}

		private:
			void refreshData() {
				PrintHelper::EnterPrint(this->toString()
					.append(":Property.refreshData.begin"));
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
					.append(":Property.refreshData.end"));

				notifyPropertyChanged(this, 0, nullptr);
			}

		public:
			string toString() const {
				stringstream ss;
				ss << "Property@" << this;
				return ss.str();
			}

		};

		/**
		 * 针对指针特化的属性的实现
		 */
		template<typename T> class Property<T*> {

			// 我认为不应该实现对指针的属性

		};

		/**
		 * 针对引用特化的属性的实现
		 */
		template<typename T> class Property<T&> {

			// 我认为不应该实现对引用的属性

		};

		/**
		 * 集合数据模型的实现
		 */
		template<typename T> class VectorModel : public Property<vector<T>> {

		public:
			// 要求数据类型支持拷贝、移动运算符
			VectorModel(vector<T>&& value) : Property(move(value)) {}

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
					_value.push_back(move(_Val));

					notifyPropertyChanged(this, 0, nullptr);

					if (dataBinding.get() != nullptr) {
					#if _ITERATOR_DEBUG_LEVEL == 2
						_DEBUG_ERROR("not allowed to push value to binded model");
					#endif /* _ITERATOR_DEBUG_LEVEL == 2 */
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
					ret = _value.insert(_Where, move(_Val));

					notifyPropertyChanged(this, 0, nullptr);

					if (dataBinding.get() != nullptr) {
					#if _ITERATOR_DEBUG_LEVEL == 2
						_DEBUG_ERROR("not allowed to insert value to binded model");
					#endif /* _ITERATOR_DEBUG_LEVEL == 2 */
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