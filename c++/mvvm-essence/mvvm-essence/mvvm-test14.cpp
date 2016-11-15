#include "stdafx.h"

#include "Model.h"
using namespace mvvm::model;

#include "DataBinding.h"
using namespace mvvm::binding;

namespace {

	enum Gender {
		Man, Woman
	};

	class Student {

	public:
		Model<Gender> gender;
		Model<string> name;
		Model<int> age;

		Student() : gender(Gender::Woman)
			, name("lucy")
			, age(23) {
		}

	};

	class StudentView {

	public:
		DependencyObject<Gender> gender;
		DependencyObject<string> name;
		DependencyObject<int> age;

		LambdaObserver observer;

		StudentView() : gender(Gender::Man)
			, name("jack"), age(11) {

			observer.set([this](void* model, int id, void* arg) {
				PrintHelper::Enter();
				PrintHelper::Print(this->toString());
				PrintHelper::Exit();
			});

			gender.addObserver(&observer);
			name.addObserver(&observer);
			age.addObserver(&observer);
		}

	public:
		string toString() const {
			stringstream ss;

			PrintHelper::Close();
			{
				ss << "StudentView2@" << this << ":{";
				ss << "Gender=" << gender.get() << ',';
				ss << "Name=" << name.get() << ',';
				ss << "Age=" << age.get() << '}';
			}
			PrintHelper::Open();

			return ss.str();
		}

	};

	/*****************************************************************

	<MainWindow>
		<StudentView id="myStudentView" gender="{student.gender OneWay}"
			name="{student.name OneWay}" age="{student.age OneWay}" />
	</MainWindow>

	*******************************************************************/

	namespace UI {

		template<typename ViewModel> class MainWindow {

		private:
			StudentView* myStudentView;

		public:
			void InitUI(ViewModel* vm) {

				myStudentView = new StudentView();
				cout << myStudentView->toString() << endl << endl;

				make_binding(&vm->student.gender, &myStudentView->gender, BindingType::OneWay);
				cout << endl;

				make_binding(&vm->student.name, &myStudentView->name, BindingType::OneWay);
				cout << endl;

				make_binding(&vm->student.age, &myStudentView->age, BindingType::OneWay);
				cout << endl;
			}

		};

	}

	namespace ViewModel {

		class MainWindow {
			friend class UI::MainWindow<MainWindow>;

		private:
			UI::MainWindow<MainWindow> mainWindow;
			Student student = Student();

		public:
			MainWindow() {
				mainWindow.InitUI(this);
			}

			void onButtonClick() {
				student.age.set(11); cout << endl;
				student.name.set("jack"); cout << endl;
				student.gender.set(Gender::Man); cout << endl;
			}

		};
	}

}

void test14() {
	ViewModel::MainWindow viewModel;
	viewModel.onButtonClick();
}