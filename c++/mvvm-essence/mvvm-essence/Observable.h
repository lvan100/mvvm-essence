#pragma once

#include <vector>
#include <functional>
using namespace std;

namespace mvvm {
	namespace model {

		/**
		 * ����ģ�����Ա仯֪ͨ�ӿ�
		 */
		struct INotifyPropertyChanged {

			/**
			 * ֪ͨ����ģ���Ѿ������仯
			 *
			 * @param mode �����仯������ģ��
			 * @param id   �����仯������
			 * @param arg  ���ԵĲ���
			 */
			virtual void onPropertyChanged(void* model, int id, void* arg) = 0;

		};

		/**
		 * ��װLambda���ʽ�Ĺ۲���
		 */
		class LambdaObserver : public INotifyPropertyChanged {

		private:
			function<void(void*, int, void*)> func;

		public:
			LambdaObserver() {}

			template<typename Lambda>
			LambdaObserver(Lambda l) {
				func = bind(l, placeholders::_1, placeholders::_2, placeholders::_3);
			}

			template<typename Lambda>
			void set(Lambda l) {
				func = bind(l, placeholders::_1, placeholders::_2, placeholders::_3);
			}

			virtual void onPropertyChanged(void* model, int id, void* arg) override {
				if (func != nullptr) {
					func(model, id, arg);
				}
			}

		};

		/**
		 * ����ģ�͹۲����б�
		 */
		template<typename Observer> class BaseObservable {

		private:
			/**
			 * ����ģ�͹۲����б�
			 */
			vector<Observer*> observerList;

		public:
			/**
			 * ��ӹ۲���
			 */
			void addObserver(Observer* observer) {
				observerList.push_back(observer);
			}

			/**
			 * �Ƴ��۲���
			 */
			void removeObserver(Observer* observer) {

				auto iter = find_if(observerList.begin(), observerList.end(),
					[&observer](Observer* p) {
					return p == observer;
				});

				if (iter != observerList.end()) {
					observerList.erase(iter);
				}
			}

			/**
			 * ֪ͨ����ģ�ͷ����仯
			 */
			void notifyPropertyChanged(void* model, int id, void* arg) {
				PrintHelper::EnterPrint(this->toString()
					.append(":BaseObservable.notifyPropertyChanged.begin"));
				{
					for (Observer* observer : observerList) {
						PrintHelper::EnterPrint(":Notify.onPropertyChanged.begin");
						{
							observer->onPropertyChanged(model, id, arg);
						}
						PrintHelper::ExitPrint(":Notify.onPropertyChanged.end");
					}
				}
				PrintHelper::ExitPrint(this->toString()
					.append(":BaseObservable.notifyPropertyChanged.end"));
			}

			string toString() const {
				stringstream ss;
				ss << "BaseObservable@" << this;
				return ss.str();
			}

		};

		/**
		 * ��������ģ�ͱ仯֪ͨ�ӿ�
		 */
		struct INotifyVectorChanged : public INotifyPropertyChanged {

		};

		/**
		 * ��������ģ�͹۲����б�
		 */
		class VectorObservable : public BaseObservable<INotifyVectorChanged> {

		};

	}
}