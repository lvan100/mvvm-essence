#pragma once

#include <vector>
#include <functional>
using namespace std;

namespace mvvm {
	namespace model {

		/**
		 * 数据模型属性变化通知接口
		 */
		struct INotifyPropertyChanged {

			/**
			 * 通知数据模型已经发生变化
			 *
			 * @param mode 发生变化的数据模型
			 * @param id   发生变化的属性
			 * @param arg  属性的参数
			 */
			virtual void onPropertyChanged(void* model, int id, void* arg) = 0;

		};

		/**
		 * 封装Lambda表达式的观察者
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
		 * 数据模型观察者列表
		 */
		template<typename Observer> class BaseObservable {

		private:
			/**
			 * 数据模型观察者列表
			 */
			vector<Observer*> observerList;

		public:
			/**
			 * 添加观察者
			 */
			void addObserver(Observer* observer) {
				observerList.push_back(observer);
			}

			/**
			 * 移除观察者
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
			 * 通知数据模型发生变化
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
		 * 集合数据模型变化通知接口
		 */
		struct INotifyVectorChanged : public INotifyPropertyChanged {

		};

		/**
		 * 集合数据模型观察者列表
		 */
		class VectorObservable : public BaseObservable<INotifyVectorChanged> {

		};

	}
}