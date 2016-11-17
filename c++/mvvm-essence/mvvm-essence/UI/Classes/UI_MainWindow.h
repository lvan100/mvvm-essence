#pragma once

#include "../../StudentView.h"

namespace UI {

	template<typename TrueView> class UI_MainWindow {

	protected:
		StudentView* myStudentView;

	protected:
		void InitUI(TrueView* view) {

			myStudentView = new StudentView();
			cout << myStudentView->toString() << endl << endl;

			make_binding(&view->student.gender, &myStudentView->gender, BindingType::OneWay);
			cout << endl;

			make_binding(&view->student.name, &myStudentView->name, BindingType::OneWay);
			cout << endl;

			make_binding(&view->student.age, &myStudentView->age, BindingType::OneWay);
			cout << endl;
		}

	};

}