#pragma once

#include <vector>
#include <sstream>
using namespace std;

#include "PrintHelper.h"

#include "IDataBinding.h"
using namespace mvvm::binding;

namespace mvvm {
	namespace model {

		/**
		 * ��������ģ�͵�ʵ��
		 */
		template<typename T> class Model : public IModel<T> {

		private:
			/**
			 * ����ֵ
			 */
			T _value;

			/**
			 * �Ƿ�ֻ��
			 */
			bool _readOnly = false;

			/**
			 * ���ݰ󶨶���
			 */
			IDataBinding<T>* dataBinding = nullptr;

		public:
			Model(T value) : _value(value) {}
			Model(T value, bool readOnly) : _value(value), _readOnly(readOnly) {}

			virtual T get() override {
				PrintHelper::getInstance()->print(this->toString().append(":Model.getValue"));
				if (dataBinding == nullptr) {
					return _value;
				} else {
					return dataBinding->get();
				}
			}

			virtual void set(T value) override {
				PrintHelper::getInstance()->enterPrint(this->toString().append(":Model.setValue.begin"));

				if (!readOnly()) {
					if (dataBinding == nullptr) {

						stringstream ss_oldValue;
						ss_oldValue << _value;

						stringstream ss_newValue;
						ss_newValue << value;

						PrintHelper::getInstance()->enterPrint(this->toString().append(":Model.setValue=")
							.append(ss_oldValue.str()).append("->").append(ss_newValue.str()));

						PrintHelper::getInstance()->exit();

						// Ҫ���������ͱ���֧��!=������
						if (this->_value != value) {
							this->_value = value;

							PrintHelper::getInstance()->enterPrint(this->toString()
								.append(":Model.notifyValueChanged.begin"));
							{
								notifyValueChanged();
							}
							PrintHelper::getInstance()->exitPrint(this->toString()
								.append(":Model.notifyValueChanged.end"));
						}

					} else {
						dataBinding->set(value);
					}
				}
				PrintHelper::getInstance()->exitPrint(this->toString().append(":Model.setValue.end"));
			}

			bool readOnly() {
				return _readOnly;
			}

			void setReadOnly(bool readOnly) {
				this->_readOnly = readOnly;
			}

			IDataBinding<T>* getDataBinding() {
				return dataBinding;
			}

			void setDataBinding(IDataBinding<T>* dataBinding) {
				PrintHelper::getInstance()->enterPrint(this->toString()
					.append(":Model.setDataBinding.begin"));
				{
					this->dataBinding = dataBinding;
					dataBinding->setTarget(this);

					this->notifyValueChanged();
				}
				PrintHelper::getInstance()->exitPrint(this->toString()
					.append(":Model.setDataBinding.end"));
			}

		private:
			/**
			 * ֵ�仯֪ͨ�б�
			 */
			vector<INotifyValueChanged*> notifyList;

		public:
			virtual void removeNotifyValueChanged(INotifyValueChanged* notify) {
				// notifyList.erase(notify);
			}

			virtual void addNotifyValueChanged(INotifyValueChanged* notify) {
				notifyList.push_back(notify);
			}

			virtual void onValueChanged(void* model) override {
				PrintHelper::getInstance()->enterPrint(this->toString()
					.append(":Model.onValueChanged"));

				PrintHelper::getInstance()->print(this->toString()
					.append(":Model.notifyValueChanged.begin"));
				{
					notifyValueChanged();
				}
				PrintHelper::getInstance()->exitPrint(this->toString()
					.append(":Model.notifyValueChanged.end"));
			}

		public:
			void notifyValueChanged() {
				for (INotifyValueChanged* notify : notifyList) {
					PrintHelper::getInstance()->enterPrint(":Notify.onValueChanged.begin");
					{
						notify->onValueChanged(this);
					}
					PrintHelper::getInstance()->exitPrint(":Notify.onValueChanged.end");
				}
			}

			string toString() {
				stringstream ss;
				ss << "Model@" << this;
				return ss.str();
			}

		};

	}
}