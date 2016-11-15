#include "stdafx.h"

#include "Model.h"
using namespace mvvm::model;

#include "DataBinding.h"
using namespace mvvm::binding;

namespace {

	enum Gender {
		Man, Woman
	};

	class Student : public BaseObservable<INotifyPropertyChanged> {

	private:
		Gender _gender;
		string _name;
		int _age;

	public:
		void set(Gender gender, string name, int age) {
			this->_gender = gender;
			this->_name = name;
			this->_age = age;
			notifyPropertyChanged(this, 0, this);
		}

		Gender getGender() {
			return _gender;
		}

		void setGender(Gender gender) {
			this->_gender = gender;
			notifyPropertyChanged(this, 1, &_gender);
		}

		string getName() {
			return _name;
		}

		void setName(string name) {
			this->_name = name;
			notifyPropertyChanged(this, 2, &_name);
		}

		int getAge() {
			return _age;
		}

		void setAge(int age) {
			this->_age = age;
			notifyPropertyChanged(this, 3, &_age);
		}

	};

	class StudentView : public INotifyPropertyChanged {

	private:
		Gender gender = Gender::Woman;
		string name = "lucy";
		int age = 23;

	public:
		virtual void onPropertyChanged(void* model, int id, void* arg) override {
			switch (id) {
			case 0: {
				Student* stu = (Student*)arg;
				gender = stu->getGender();
				name = stu->getName();
				age = stu->getAge();
			}
					break;
			case 1: {
				gender = *(Gender*)arg;
			}
					break;
			case 2: {
				name = *(string*)arg;
			}
					break;
			case 3: {
				age = *(int*)arg;
			}
					break;
			default:
				break;
			}

			PrintHelper::Print(this->toString());
		}

	public:
		string toString() const {
			stringstream ss;

			ss << "StudentView@" << this << ":{";
			ss << "Gender=" << gender << ',';
			ss << "Name=" << name << ',';
			ss << "Age=" << age << '}';

			return ss.str();
		}

	};

}

void test13() {

	Student student;
	StudentView stuView;

	cout << stuView.toString() << endl << endl;

	student.addObserver(&stuView);

	student.setAge(11); cout << endl;
	student.setName("jack"); cout << endl;
	student.setGender(Gender::Man); cout << endl;

	student.set(Gender::Woman, "piter", 40); cout << endl;
}