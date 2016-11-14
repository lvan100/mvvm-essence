#include "stdafx.h"

#include <list>
#include <vector>
#include <cassert>
#include <sstream>
#include <iostream>
using namespace std;

#include "Model.h"
using namespace mvvm::model;

#include "DataBinding.h"
using namespace mvvm::binding;

#define SafeAssert(x) PrintHelper::Close(); assert(x); PrintHelper::Open()

template<typename T> struct PrintModel : public INotifyPropertyChanged {

	virtual void onPropertyChanged(void* model, int id, void* arg) override {
		PrintHelper::Enter();

		stringstream ss_model;
		ss_model << ((Model<T>*)model)->get();

		PrintHelper::Print(this->toString().append(":").append(ss_model.str()));
		PrintHelper::Exit();
	}

	string toString() const {
		stringstream ss;
		ss << "PrintModel@" << this;
		return ss.str();
	}

};

PrintModel<int> printIntModel;
PrintModel<float> printFloatModel;
PrintModel<double> printDoubleModel;

Model<int> mi0(1);
DependencyObject<int> mi1(2), mi2(3, true);

void test1() {

	mi0.set(11); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(mi1.get() == 2);
	SafeAssert(mi2.get() == 3);

	mi1.set(22); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(mi1.get() == 22);
	SafeAssert(mi2.get() == 3);

	mi2.set(33); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(mi1.get() == 22);
	SafeAssert(mi2.get() == 3);

	mi0.addObserver(&printIntModel);
	mi1.addObserver(&printIntModel);
	mi2.addObserver(&printIntModel);

	mi0.set(111); cout << endl;
	SafeAssert(mi0.get() == 111);
	SafeAssert(mi1.get() == 22);
	SafeAssert(mi2.get() == 3);

	mi1.set(222); cout << endl;
	SafeAssert(mi0.get() == 111);
	SafeAssert(mi1.get() == 222);
	SafeAssert(mi2.get() == 3);

	mi2.set(333); cout << endl;
	SafeAssert(mi0.get() == 111);
	SafeAssert(mi1.get() == 222);
	SafeAssert(mi2.get() == 3);

	mi1.setDataBinding(make_binding<int, int>(BindingType::TwoWay, &mi0));
	cout << endl;

	SafeAssert(mi0.get() == 111);
	SafeAssert(mi1.get() == 111);
	SafeAssert(mi2.get() == 3);

	mi0.set(11); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(mi1.get() == 11);
	SafeAssert(mi2.get() == 3);

	mi1.set(22); cout << endl;
	SafeAssert(mi0.get() == 22);
	SafeAssert(mi1.get() == 22);
	SafeAssert(mi2.get() == 3);

	mi2.set(33); cout << endl;
	SafeAssert(mi0.get() == 22);
	SafeAssert(mi1.get() == 22);
	SafeAssert(mi2.get() == 3);

	mi2.setDataBinding(make_binding<int, int>(BindingType::TwoWay, &mi1));
	cout << endl;

	SafeAssert(mi0.get() == 22);
	SafeAssert(mi1.get() == 22);
	SafeAssert(mi2.get() == 22);

	mi0.set(1); cout << endl;
	SafeAssert(mi0.get() == 1);
	SafeAssert(mi1.get() == 1);
	SafeAssert(mi2.get() == 1);

	mi1.set(2); cout << endl;
	SafeAssert(mi0.get() == 2);
	SafeAssert(mi1.get() == 2);
	SafeAssert(mi2.get() == 2);

	mi2.set(3); cout << endl;
	SafeAssert(mi0.get() == 2);
	SafeAssert(mi1.get() == 2);
	SafeAssert(mi2.get() == 2);
}

void test2() {

	Model<int> mi0(1);
	DependencyObject<float> mf0(2.20f);

	mi0.addObserver(&printIntModel);
	mf0.addObserver(&printFloatModel);

	mi0.set(11); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(mf0.get() == 2.20f);

	mf0.set(22.20f); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(mf0.get() == 22.20f);

	mf0.setDataBinding(make_binding<int, float>(BindingType::TwoWay, &mi0));
	cout << endl;

	SafeAssert(mi0.get() == 11);
	SafeAssert(mf0.get() == 11);

	mi0.set(111); cout << endl;
	SafeAssert(mi0.get() == 111);
	SafeAssert(mf0.get() == 111);

	mf0.set(222.20f); cout << endl;
	SafeAssert(mi0.get() == 222);
	SafeAssert(mf0.get() == 222);
}

struct Integer {

	int value = 0;

	operator int() {
		return value;
	}

	Integer(int value) {
		this->value = value;
	}

	bool operator != (Integer& i) {
		return this->value != i.value;
	}

};

inline bool operator == (const Integer& i, int value) {
	return i.value == value;
}

template<class _Traits> inline
basic_ostream<char, _Traits>& operator<<(
	basic_ostream<char, _Traits>& _Ostr, const Integer& i)
{
	return (_Ostr << i.value);
}

PrintModel<Integer> printIntegerModel;

void test6() {

	Model<int> mi0(1);
	DependencyObject<Integer> mI0(2);

	mi0.addObserver(&printIntModel);
	mI0.addObserver(&printIntegerModel);

	mi0.set(11); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(mI0.get() == 2);

	mI0.set(22); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(mI0.get() == 22);

	mI0.setDataBinding(make_binding<int, Integer>(BindingType::TwoWay, &mi0));
	cout << endl;

	SafeAssert(mi0.get() == 11);
	SafeAssert(mI0.get() == 11);

	mi0.set(111); cout << endl;
	SafeAssert(mi0.get() == 111);
	SafeAssert(mI0.get() == 111);

	mI0.set(222); cout << endl;
	SafeAssert(mi0.get() == 222);
	SafeAssert(mI0.get() == 222);
}

struct Double {

	double value = 0.0;

	operator double() {
		return value;
	}

	Double(double value) {
		PrintHelper::Print(string("{") + toString(this)
			+ ":Double:double" + " <- " + toString(value) + "}");
		this->value = value;
	}

	Double(const Double& d) {
		PrintHelper::Print(string("{") + toString(this)
			+ ":Double:const Double&" + " <- " + toString(&d) + "}");
		this->value = d.value;
	}

	Double(Double&& d) {
		PrintHelper::Print(string("{") + toString(this)
			+ ":Double:Double&&" + " <- " + toString(&d) + "}");
		this->value = move(d.value);
	}

	Double& operator= (double value) {
		PrintHelper::Print(string("{") + toString(this)
			+ ":Double:= const Double&" + " <- " + toString(value) + "}");
		this->value = value;
		return *this;
	}

	Double& operator= (const Double& d) {
		PrintHelper::Print(string("{") + toString(this)
			+ ":Double:= const Double&" + " <- " + toString(&d) + "}");
		this->value = d.value;
		return *this;
	}

	Double& operator= (Double&& d) {
		PrintHelper::Print(string("{") + toString(this)
			+ ":Double:= Double&&" + " <- " + toString(&d) + "}");
		this->value = move(d.value);
		return *this;
	}

	bool operator != (Double& i) {
		return this->value != i.value;
	}

	string toString(const Double* p) const {
		stringstream ss;
		if (p != nullptr) {
			ss << "Double@" << p << "=" << p->value;
		}
		return ss.str();
	}

	string toString(double value) const {
		stringstream ss;
		ss << value;
		return ss.str();
	}

};

inline bool operator == (const Double& d, double value) {
	return d.value == value;
}

template<class _Traits> inline
basic_ostream<char, _Traits>& operator<<(
	basic_ostream<char, _Traits>& _Ostr, const Double& d)
{
	return (_Ostr << d.value);
}

template<> struct ValueConverter<Double, Integer> {

	static void convert(const Double& source, Integer& target) {
		target.value = int(source.value);
	}

	static Double reverseConvert(Integer&& value) {
		return move(value.value);
	}

};

PrintModel<Double> printSDoubleModel;

void test7() {

	Model<Double> mD0(1.10);
	DependencyObject<Integer> mI0(2);

	mD0.addObserver(&printSDoubleModel);
	mI0.addObserver(&printIntegerModel);

	mD0.set(11.10); cout << endl;
	SafeAssert(mD0.get() == 11.10);
	SafeAssert(mI0.get() == 2);

	mI0.set(22); cout << endl;
	SafeAssert(mD0.get() == 11.10);
	SafeAssert(mI0.get() == 22);

	mI0.setDataBinding(make_binding<Double, Integer>(BindingType::TwoWay, &mD0));
	cout << endl;

	SafeAssert(mD0.get() == 11.10);
	SafeAssert(mI0.get() == 11);

	mD0.set(111.10); cout << endl;
	SafeAssert(mD0.get() == 111.10);
	SafeAssert(mI0.get() == 111);

	mI0.set(222); cout << endl;
	SafeAssert(mD0.get() == 222);
	SafeAssert(mI0.get() == 222);
}

template<> struct ValueConverter<Integer, Double> {

	static void convert(const Integer& source, Double& target) {
		target.value = source.value;
	}

	static Integer reverseConvert(Double&& value) {
		return move(int(value.value));
	}

};

void test7_2() {

	Model<Integer> mI0(2);
	DependencyObject<Double> mD0(1.10);

	mI0.addObserver(&printIntegerModel);
	mD0.addObserver(&printSDoubleModel);

	mI0.set(22); cout << endl;
	SafeAssert(mI0.get() == 22);
	SafeAssert(mD0.get() == 1.10);

	mD0.set(11.10); cout << endl;
	SafeAssert(mI0.get() == 22);
	SafeAssert(mD0.get() == 11.10);

	mD0.setDataBinding(make_binding<Integer, Double>(BindingType::TwoWay, &mI0));
	cout << endl;

	SafeAssert(mI0.get() == 22);
	SafeAssert(mD0.get() == 22);

	mI0.set(222); cout << endl;
	SafeAssert(mI0.get() == 222);
	SafeAssert(mD0.get() == 222);

	mD0.set(111.10); cout << endl;
	SafeAssert(mI0.get() == 111);
	SafeAssert(mD0.get() == 111);
}

/**
 * 使用非特化模板的值转换器
 */
struct IntVectorAndIntValueConverter {

	static void convert(const vector<int>& source, int& target) {
		if (source.size() > 0) {
			target = int(source.at(0));
		}
	}

	static vector<int> reverseConvert(int&& value) {
		return move(vector<int>(1, value));
	}

};

template<class _Traits> inline
basic_ostream<char, _Traits>& operator<<(
	basic_ostream<char, _Traits>& _Ostr, const vector<int>& vi)
{
	_Ostr << '[';
	for (int i : vi) {
		_Ostr << i << ',';
	}
	_Ostr << '\b' << ']';
	return _Ostr;
}

PrintModel<vector<int>> printIntVectorModel;

void test8() {

	Model<vector<int>> miv0(vector<int>(2, 2));
	DependencyObject<int> mi0(1);

	miv0.addObserver(&printIntVectorModel);
	mi0.addObserver(&printIntModel);

	miv0.set(vector<int>(2, 22)); cout << endl;
	SafeAssert(miv0.get() == vector<int>(2, 22));
	SafeAssert(mi0.get() == 1);

	mi0.set(11); cout << endl;
	SafeAssert(miv0.get() == vector<int>(2, 22));
	SafeAssert(mi0.get() == 11);

	mi0.setDataBinding(make_binding<vector<int>, int, IntVectorAndIntValueConverter>(BindingType::TwoWay, &miv0));
	cout << endl;

	SafeAssert(miv0.get() == vector<int>(2, 22));
	SafeAssert(mi0.get() == 22);

	miv0.set(vector<int>(2, 222)); cout << endl;
	SafeAssert(miv0.get() == vector<int>(2, 222));
	SafeAssert(mi0.get() == 222);

	mi0.set(111); cout << endl;
	SafeAssert(miv0.get() == vector<int>(1, 111));
	SafeAssert(mi0.get() == 111);
}

template<> struct ValueConverter<int, vector<int>> {

	static void convert(const int& source, vector<int>& target) {
		target = vector<int>(1, source);
	}

	static int reverseConvert(vector<int>&& value) {
		if (value.size() > 0) {
			return move(value.at(0));
		} else {
			return 0;
		}
	}

};

void test9() {

	Model<int> mi0(1);
	DependencyObject<vector<int>> miv0(vector<int>(2, 2));

	mi0.addObserver(&printIntModel);
	miv0.addObserver(&printIntVectorModel);

	mi0.set(11); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(miv0.get() == vector<int>(2, 2));

	miv0.set(vector<int>(2, 22)); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(miv0.get() == vector<int>(2, 22));

	miv0.setDataBinding(make_binding<int, vector<int>>(BindingType::TwoWay, &mi0));
	cout << endl;

	SafeAssert(mi0.get() == 11);
	SafeAssert(miv0.get() == vector<int>(1, 11));

	mi0.set(111); cout << endl;
	SafeAssert(mi0.get() == 111);
	SafeAssert(miv0.get() == vector<int>(1, 111));

	miv0.set(vector<int>(2, 222)); cout << endl;
	SafeAssert(mi0.get() == 222);
	SafeAssert(miv0.get() == vector<int>(1, 222));
}

template<> struct ValueConverter<list<float>, vector<int>> {

	static void convert(const list<float>& source, vector<int>& target) {
		target.clear();
		target.insert(target.begin(), source.begin(), source.end());
	}

	static list<float> reverseConvert(vector<int>&& value) {
		return move(list<float>(value.begin(), value.end()));
	}

};

template<class _Traits> inline
basic_ostream<char, _Traits>& operator<<(
	basic_ostream<char, _Traits>& _Ostr, const list<float>& vi)
{
	_Ostr << '[';
	for (float i : vi) {
		_Ostr << i << ',';
	}
	_Ostr << '\b' << ']';
	return _Ostr;
}

PrintModel<list<float>> printFloatListModel;

void test10() {

	Model<list<float>> mfl0(list<float>(3, 1.1f));
	DependencyObject<vector<int>> miv0(vector<int>(2, 2));

	mfl0.addObserver(&printFloatListModel);
	miv0.addObserver(&printIntVectorModel);

	mfl0.set(list<float>(3, 11.1f)); cout << endl;
	SafeAssert(mfl0.get() == list<float>(3, 11.1f));
	SafeAssert(miv0.get() == vector<int>(2, 2));

	miv0.set(vector<int>(2, 22)); cout << endl;
	SafeAssert(mfl0.get() == list<float>(3, 11.1f));
	SafeAssert(miv0.get() == vector<int>(2, 22));

	miv0.setDataBinding(make_binding<list<float>, vector<int>>(BindingType::TwoWay, &mfl0));
	cout << endl;

	SafeAssert(mfl0.get() == list<float>(3, 11.1f));
	SafeAssert(miv0.get() == vector<int>(3, 11));

	mfl0.set(list<float>(3, 111.1f)); cout << endl;
	SafeAssert(mfl0.get() == list<float>(3, 111.1f));
	SafeAssert(miv0.get() == vector<int>(3, 111));

	miv0.set(vector<int>(2, 222)); cout << endl;
	SafeAssert(mfl0.get() == list<float>(2, 222));
	SafeAssert(miv0.get() == vector<int>(2, 222));
}

void test11() {

	Model<list<float>> mfl0(list<float>(3, 1.1f));
	VectorModel<int> miv0(vector<int>(2, 2));

	mfl0.addObserver(&printFloatListModel);
	miv0.addObserver(&printIntVectorModel);

	mfl0.set(list<float>(3, 11.1f)); cout << endl;
	SafeAssert(mfl0.get() == list<float>(3, 11.1f));
	SafeAssert(miv0.get() == vector<int>(2, 2));

	miv0 = vector<int>(2, 22); cout << endl;
	SafeAssert(mfl0.get() == list<float>(3, 11.1f));
	SafeAssert(miv0.get() == vector<int>(2, 22));

	miv0.setDataBinding(make_binding<list<float>, vector<int>>(BindingType::TwoWay, &mfl0));
	cout << endl;

	SafeAssert(mfl0.get() == list<float>(3, 11.1f));
	SafeAssert(miv0.get() == vector<int>(3, 11));

	mfl0.set(list<float>(3, 111.1f)); cout << endl;
	SafeAssert(mfl0.get() == list<float>(3, 111.1f));
	SafeAssert(miv0.get() == vector<int>(3, 111));

	//miv0.push_back(5); cout << endl;
	//SafeAssert(mfl0.get() == list<float>({ 111,111,111,5 }));
	//SafeAssert(miv0.get() == vector<int>({ 111,111,111,5 }));

	//auto iter = miv0.insert(miv0.get().begin(), 15); cout << endl;
	//SafeAssert(mfl0.get() == list<float>({ 15,111,111,111,5 }));
	//SafeAssert(miv0.get() == vector<int>({ 15,111,111,111,5 }));

	//miv0.insert(iter, 25); cout << endl;
	//SafeAssert(mfl0.get() == list<float>({ 15,111,111,111,5,25 }));
	//SafeAssert(miv0.get() == vector<int>({ 15,111,111,111,5,25 }));
}

template<> struct ValueConverter<vector<int>, list<float>> {

	static void convert(const vector<int>& source, list<float>& target) {
		target.clear();
		target.insert(target.begin(), source.begin(), source.end());
	}

	static vector<int> reverseConvert(list<float>&& value) {
		return move(vector<int>(value.begin(), value.end()));
	}

};

void test12() {

	VectorModel<int> miv0(vector<int>(2, 2));
	DependencyObject<list<float>> mfl0(list<float>(3, 1.1f));

	miv0.addObserver(&printIntVectorModel);
	mfl0.addObserver(&printFloatListModel);

	miv0 = vector<int>(2, 22); cout << endl;
	SafeAssert(miv0.get() == vector<int>(2, 22));
	SafeAssert(mfl0.get() == list<float>(3, 1.1f));

	mfl0.set(list<float>(3, 11.1f)); cout << endl;
	SafeAssert(miv0.get() == vector<int>(2, 22));
	SafeAssert(mfl0.get() == list<float>(3, 11.1f));

	mfl0.setDataBinding(make_binding<vector<int>, list<float>>(BindingType::TwoWay, &miv0));
	cout << endl;

	SafeAssert(miv0.get() == vector<int>(2, 22));
	SafeAssert(mfl0.get() == list<float>(2, 22));

	miv0.push_back(5); cout << endl;
	SafeAssert(miv0.get() == vector<int>({ 22,22,5 }));
	SafeAssert(mfl0.get() == list<float>({ 22,22,5 }));

	auto iter = miv0.insert(miv0.get().begin(), 15); cout << endl;
	SafeAssert(miv0.get() == vector<int>({ 15,22,22,5 }));
	SafeAssert(mfl0.get() == list<float>({ 15,22,22,5 }));

	miv0.insert(iter, 25); cout << endl;
	SafeAssert(miv0.get() == vector<int>({ 25,15,22,22,5 }));
	SafeAssert(mfl0.get() == list<float>({ 25,15,22,22,5 }));

	mfl0.set(list<float>(3, 111.1f)); cout << endl;
	SafeAssert(miv0.get() == vector<int>(3, 111));
	SafeAssert(mfl0.get() == list<float>(3, 111));
}

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

class Student2 {

public:
	Model<Gender> gender;
	Model<string> name;
	Model<int> age;

	Student2() : gender(Gender::Woman)
		, name("lucy")
		, age(23) {
	}
};

class StudentView2 :public INotifyPropertyChanged {

public:
	DependencyObject<Gender> gender;
	DependencyObject<string> name;
	DependencyObject<int> age;

	StudentView2() : gender(Gender::Man)
		, name("jack"), age(11) {

		gender.addObserver(this);
		name.addObserver(this);
		age.addObserver(this);
	}

	virtual void onPropertyChanged(void* model, int id, void* arg) override {
		PrintHelper::Enter();
		PrintHelper::Print(this->toString());
		PrintHelper::Exit();
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

void test14() {

	Student2 student;
	StudentView2 stuView;

	cout << stuView.toString() << endl << endl;

	stuView.gender.setDataBinding(make_binding<Gender, Gender>(BindingType::OneWay, &student.gender));
	cout << endl;

	stuView.name.setDataBinding(make_binding<string, string>(BindingType::OneWay, &student.name));
	cout << endl;

	stuView.age.setDataBinding(make_binding<int, int>(BindingType::OneWay, &student.age));
	cout << endl;

	student.age.set(11); cout << endl;
	student.name.set("jack"); cout << endl;
	student.gender.set(Gender::Man); cout << endl;
}

int main()
{
	test1();

	mi0.set(11); cout << endl;
	SafeAssert(mi0.get() == 11);
	SafeAssert(mi1.get() == 11);
	SafeAssert(mi2.get() == 11);

	mi1.set(22); cout << endl;
	SafeAssert(mi0.get() == 22);
	SafeAssert(mi1.get() == 22);
	SafeAssert(mi2.get() == 22);

	mi2.set(33); cout << endl;
	SafeAssert(mi0.get() == 22);
	SafeAssert(mi1.get() == 22);
	SafeAssert(mi2.get() == 22);

	test2();

	test6();

	test7();
	test7_2();

	test8();
	test9();

	test10();

	test11();
	test12();

	test13();
	test14();

	return 0;
}