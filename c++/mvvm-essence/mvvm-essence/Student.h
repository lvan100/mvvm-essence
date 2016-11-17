#pragma once

#include "Model.h"
using namespace mvvm::model;

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