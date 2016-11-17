#pragma once

#include "UI/Classes/UI_MainWindow.h"

class MainWindow
	: public Framework::BaseView
	, public UI::UI_MainWindow<MainWindow> {

	friend class UI::UI_MainWindow<MainWindow>;
	typedef UI::UI_MainWindow<MainWindow> BaseUI;

private:
	Student student;

public:
	MainWindow() {
		BaseUI::InitUI(this);
	}

	void onButtonClick() {
		student.age.set(11); cout << endl;
		student.name.set("jack"); cout << endl;
		student.gender.set(Gender::Man); cout << endl;
	}

};