#pragma once

#include "Model.h"
using namespace mvvm::model;

enum Gender {
	Man, Woman
};

class Student {

public:
	Model<int> age;
	Model<string> name;
	Model<Gender> gender;

	Student() : gender(Gender::Woman)
		, name("lucy")
		, age(23) {
	}

};