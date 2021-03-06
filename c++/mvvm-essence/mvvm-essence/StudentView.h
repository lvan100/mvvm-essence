#pragma once

#include "Student.h"

#include "BaseView.h"
using namespace Framework;

#include "DataBinding.h"
using namespace mvvm::binding;

#include "UI/Classes/UI_StudentView.h"

class StudentView
	: public Framework::BaseView
	, public UI::UI_StudentView<StudentView> {

	friend class UI::UI_StudentView<StudentView>;
	typedef UI::UI_StudentView<StudentView> BaseUI;

public:
	Property<int> age;
	Property<string> name;
	Property<Gender> gender;

	LambdaObserver observer;

	StudentView(BaseView* parent)
		: BaseView(parent)
		, gender(Gender::Man)
		, name("jack")
		, age(11) {

		BaseUI::InitUI(this);

		age.addObserver(&observer);
		name.addObserver(&observer);
		gender.addObserver(&observer);

		observer.set([this](void* model, int id, void* arg) {
			PrintHelper::Enter();
			PrintHelper::Print(this->toString());
			PrintHelper::Exit();
		});
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