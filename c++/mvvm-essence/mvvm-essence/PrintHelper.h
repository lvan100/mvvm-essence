#pragma once

#include <string>
#include <memory>
#include <iostream>
using namespace std;

class PrintHelper
{
public:
	static PrintHelper* getInstance() {
		static unique_ptr<PrintHelper> printHelper;
		if (printHelper.get() == nullptr) {
			printHelper.reset(new PrintHelper());
		}
		return printHelper.get();
	}

private:
	PrintHelper() {
	}

private:
	int deep = -1;

public:
	void enter() {
		deep++;
	}

	void enterPrint(string str) {
		deep++;
		print(str);
	}

	void exit() {
		deep--;
	}

	void exitPrint(string str) {
		print(str);
		deep--;
	}

	void print(string str) {
		for (int i = 0; i < deep; i++) {
			cout << "\t";
		}
		cout << str << endl;
	}

};