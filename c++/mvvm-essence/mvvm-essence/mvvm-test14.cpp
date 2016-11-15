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

			ss << "StudentView2@" << this << ":{";
			ss << "Gender=" << gender.get() << ',';
			ss << "Name=" << name.get() << ',';
			ss << "Age=" << age.get() << '}';

			return ss.str();
		}

	};

}

void test14() {

	Student student;
	StudentView stuView;

	cout << stuView.toString() << endl << endl;

	make_binding(&student.gender, &stuView.gender, BindingType::OneWay);
	cout << endl;

	make_binding(&student.name, &stuView.name, BindingType::OneWay);
	cout << endl;

	make_binding(&student.age, &stuView.age, BindingType::OneWay);
	cout << endl;

	student.age.set(11); cout << endl;
	student.name.set("jack"); cout << endl;
	student.gender.set(Gender::Man); cout << endl;
}