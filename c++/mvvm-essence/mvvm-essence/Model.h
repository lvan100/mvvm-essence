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
		 * ÿ�������������Լ������ݿ��������ײ����ݷ����仯ʱ������ˢ��
		 * ���ݲ����������������ں�����ʹ�ù���������ײ�����û�з����仯��
		 * ����Ҫ��λ�ȡģ�͵�ֵʱЧ�ʸ��ߣ���Ϊ����ÿ�ζ�Ҫִ��һ��ת����
		 */

		/**
		 * ����ģ�͵�ʵ��
		 */
		template<typename T> class Model : public BaseObservable<INotifyPropertyChanged> {

		protected:
			/**
			 * ����ֵ
			 */
			T _value;

			/**
			 * �Ƿ�ֻ��
			 */
			bool _readOnly = false;
			
		public:
			// Ҫ����������֧�ֿ������ƶ������
			Model(T&& value) : _value(move(value)) {}
			Model(T&& value, bool readOnly) : _value(move(value)), _readOnly(readOnly) {}

			bool readOnly() {
				return _readOnly;
			}

			void setReadOnly(bool readOnly) {
				this->_readOnly = readOnly;
			}

			/**
			 * ��������ģ��ֵ�����ã�������Ҫ����ֵ���ܱ��޸�
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

						// Ҫ����������֧��!=������
						if (this->_value != value) {

							// Ҫ����������֧��=������
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
		 * ���ָ���ػ�������ģ�͵�ʵ��
		 */
		template<typename T> class Model<T*> {

			// ����Ϊ��Ӧ��ʵ�ֶ�ָ�������ģ��

		};

		/**
		 * ��������ػ�������ģ�͵�ʵ��
		 */
		template<typename T> class Model<T&> {

			// ����Ϊ��Ӧ��ʵ�ֶ����õ�����ģ��

		};

		/**
		 * ���������ʵ��
		 */
		template<typename T> class DependencyObject
			: public Model<T> /* ������λ�̳� */
			, public INotifyPropertyChanged {

		protected:
			/**
			 * ���ݰ󶨶���
			 */
			unique_ptr<IDataBinding<T>> dataBinding;

		public:
			// Ҫ����������֧�ֿ������ƶ������
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
		 * ���ָ���ػ������������ʵ��
		 */
		template<typename T> class DependencyObject<T*> {

			// ����Ϊ��Ӧ��ʵ�ֶ�ָ�����������

		};

		/**
		 * ��������ػ������������ʵ��
		 */
		template<typename T> class DependencyObject<T&> {

			// ����Ϊ��Ӧ��ʵ�ֶ����õ���������

		};

		/**
		 * ��������ģ�͵�ʵ��
		 */
		template<typename T> class VectorModel : public DependencyObject<vector<T>> {

		public:
			// Ҫ����������֧�ֿ������ƶ������
			VectorModel(vector<T>&& value) : DependencyObject(move(value)) {}
			VectorModel(vector<T>&& value, bool readOnly) : DependencyObject(move(value)��readOnly) {}

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
			 * ֻ�����ԴModel���ݽ��д˲���
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
			 * ֻ�����ԴModel���ݽ��д˲���
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