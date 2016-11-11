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
		PrintHelper::getInstance()->enter();

		stringstream ss_model;
		ss_model << ((Model<T>*)model)->get();

		PrintHelper::getInstance()->print(string().append("PrintModel:").append(ss_model.str()));
		PrintHelper::getInstance()->exit();
	}
};

template<typename T> struct PrintModel<T*> : public INotifyValueChanged {

	virtual void onValueChanged(void* model) override {
		PrintHelper::getInstance()->enter();

		stringstream ss_model;
		ss_model << *(((Model<T*>*)model)->get());

		PrintHelper::getInstance()->print(string().append("PrintModel:").append(ss_model.str()));
		PrintHelper::getInstance()->exit();
	}
};

PrintModel<int> printIntModel;
PrintModel<int*> printIntPtrModel;
PrintModel<float> printFloatModel;
PrintModel<double> printDoubleModel;
PrintModel<double*> printDoublePtrModel;

void test1() {

	Model<int> mi0(1), mi1(2), mi2(3, true);

	mi0.set(11); cout << endl;
	mi1.set(22); cout << endl;
	mi2.set(33); cout << endl;

	mi0.addNotifyValueChanged(&printIntModel);
	mi1.addNotifyValueChanged(&printIntModel);
	mi2.addNotifyValueChanged(&printIntModel);

	mi0.set(111); cout << endl;
	mi1.set(222); cout << endl;
	mi2.set(333); cout << endl;

	DataBinding<int, int> dii0(BindingType::TwoWay, &mi0);
	mi1.setDataBinding(&dii0); cout << endl;

	mi0.set(11); cout << endl;
	mi1.set(22); cout << endl;
	mi2.set(33); cout << endl;

	DataBinding<int, int> dii1(BindingType::TwoWay, &mi1);
	mi2.setDataBinding(&dii1); cout << endl;

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

	DataBinding<int, float> dif0(BindingType::TwoWay, &mi0);
	mf0.setDataBinding(&dif0); cout << endl;

	mi0.set(111); cout << endl;
	mf0.set(222.20f); cout << endl;
}

void test3() {

	Model<int> mi0(1);
	Model<double*> mdp0(new double(2.20));

	mi0.addNotifyValueChanged(&printIntModel);
	mdp0.addNotifyValueChanged(&printDoublePtrModel);

	mi0.set(11); cout << endl;
	mdp0.set(new double(22.20)); cout << endl;

	DataBinding<int, double*> dif0(BindingType::TwoWay, &mi0);
	mdp0.setDataBinding(&dif0); cout << endl;

	mi0.set(111); cout << endl;
	mdp0.set(new double(222.20)); cout << endl;
}

void test4() {

	Model<int*> mip0(new int(1));
	Model<double> mdp0(2.20);

	mip0.addNotifyValueChanged(&printIntPtrModel);
	mdp0.addNotifyValueChanged(&printDoubleModel);

	mip0.set(new int(11)); cout << endl;
	mdp0.set(22.20); cout << endl;

	DataBinding<int*, double> dif0(BindingType::TwoWay, &mip0);
	mdp0.setDataBinding(&dif0); cout << endl;

	mip0.set(new int(111)); cout << endl;
	mdp0.set(222.20); cout << endl;
}

void test5() {

	Model<int*> mip0(new int(1));
	Model<double*> mdp0(new double(2.20));

	mip0.addNotifyValueChanged(&printIntPtrModel);
	mdp0.addNotifyValueChanged(&printDoublePtrModel);

	mip0.set(new int(11)); cout << endl;
	mdp0.set(new double(22.20)); cout << endl;

	DataBinding<int*, double*> dif0(BindingType::TwoWay, &mip0);
	mdp0.setDataBinding(&dif0); cout << endl;

	mip0.set(new int(111)); cout << endl;
	mdp0.set(new double(222.20)); cout << endl;
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

	DataBinding<int, Integer> dif0(BindingType::TwoWay, &mi0);
	mI0.setDataBinding(&dif0); cout << endl;

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

PrintModel<Double> printSDoubleModel;

void test7() {

	Model<Double> mD0(1.10);
	Model<Integer> mI0(2);

	mD0.addNotifyValueChanged(&printSDoubleModel);
	mI0.addNotifyValueChanged(&printIntegerModel);

	mD0.set(11.10); cout << endl;
	mI0.set(22); cout << endl;

	DataBinding<Double, Integer> dif0(BindingType::TwoWay, &mD0);
	mI0.setDataBinding(&dif0); cout << endl;

	mD0.set(111.10); cout << endl;
	mI0.set(222); cout << endl;
}

int main()
{
	test1();
	test2();

	test3();
	test4();
	test5();

	test6();
	test7();

	return 0;
}