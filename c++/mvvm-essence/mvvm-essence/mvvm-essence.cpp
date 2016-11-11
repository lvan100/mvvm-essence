#include "stdafx.h"

#include <sstream>
#include <iostream>
using namespace std;

#include "Model.h"
using namespace mvvm::model;

#include "DataBinding.h"
using namespace mvvm::binding;

template<typename T> struct PrintModel : public INotifyValueChanged {

	virtual void onValueChanged(void* model) override {
		PrintHelper::Enter();

		stringstream ss_model;
		ss_model << ((Model<T>*)model)->get();

		PrintHelper::Print(this->toString().append(":").append(ss_model.str()));
		PrintHelper::Exit();
	}

	string toString() {
		stringstream ss;
		ss << "PrintModel@" << this;
		return ss.str();
	}

};

PrintModel<int> printIntModel;
PrintModel<float> printFloatModel;
PrintModel<double> printDoubleModel;

Model<int> mi0(1), mi1(2), mi2(3, true);

void test1() {

	mi0.set(11); cout << endl;
	mi1.set(22); cout << endl;
	mi2.set(33); cout << endl;

	mi0.addNotifyValueChanged(&printIntModel);
	mi1.addNotifyValueChanged(&printIntModel);
	mi2.addNotifyValueChanged(&printIntModel);

	mi0.set(111); cout << endl;
	mi1.set(222); cout << endl;
	mi2.set(333); cout << endl;

	mi1.setDataBinding(make_binding<int, int>(BindingType::TwoWay, &mi0));
	cout << endl;

	mi0.set(11); cout << endl;
	mi1.set(22); cout << endl;
	mi2.set(33); cout << endl;

	mi2.setDataBinding(make_binding<int, int>(BindingType::TwoWay, &mi1));
	cout << endl;

	mi0.set(1); cout << endl;
	mi1.set(2); cout << endl;
	mi2.set(3); cout << endl;
}

void test2() {

	Model<int> mi0(1);
	Model<float> mf0(2.20f);

	mi0.addNotifyValueChanged(&printIntModel);
	mf0.addNotifyValueChanged(&printFloatModel);

	mi0.set(11); cout << endl;
	mf0.set(22.20f); cout << endl;

	mf0.setDataBinding(make_binding<int, float>(BindingType::TwoWay, &mi0));
	cout << endl;

	mi0.set(111); cout << endl;
	mf0.set(222.20f); cout << endl;
}

struct Integer {

	int value;

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

template<class _Traits> inline
basic_ostream<char, _Traits>& operator<<(
	basic_ostream<char, _Traits>& _Ostr, Integer i)
{
	return (_Ostr << i.value);
}

PrintModel<Integer> printIntegerModel;

void test6() {

	Model<int> mi0(1);
	Model<Integer> mI0(2);

	mi0.addNotifyValueChanged(&printIntModel);
	mI0.addNotifyValueChanged(&printIntegerModel);

	mi0.set(11); cout << endl;
	mI0.set(22); cout << endl;

	mI0.setDataBinding(make_binding<int, Integer>(BindingType::TwoWay, &mi0));
	cout << endl;

	mi0.set(111); cout << endl;
	mI0.set(222); cout << endl;
}

struct Double {

	double value;

	operator double() {
		return value;
	}

	Double(double value) {
		this->value = value;
	}

	bool operator != (Double& i) {
		return this->value != i.value;
	}

};

template<class _Traits> inline
basic_ostream<char, _Traits>& operator<<(
	basic_ostream<char, _Traits>& _Ostr, Double d)
{
	return (_Ostr << d.value);
}

template<> struct ValueConverter<Double, Integer> {

	Integer convert(Double value) {
		return int(value.value);
	}

	Double reverseConvert(Integer value) {
		return value.value;
	}

};

PrintModel<Double> printSDoubleModel;

void test7() {

	Model<Double> mD0(1.10);
	Model<Integer> mI0(2);

	mD0.addNotifyValueChanged(&printSDoubleModel);
	mI0.addNotifyValueChanged(&printIntegerModel);

	mD0.set(11.10); cout << endl;
	mI0.set(22); cout << endl;

	mI0.setDataBinding(make_binding<Double, Integer>(BindingType::TwoWay, &mD0));
	cout << endl;

	mD0.set(111.10); cout << endl;
	mI0.set(222); cout << endl;
}

int main()
{
	test1();

	mi0.set(11); cout << endl;
	mi1.set(22); cout << endl;
	mi2.set(33); cout << endl;

	test2();

	test6();
	test7();

	return 0;
}