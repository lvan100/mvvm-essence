#pragma once

#include <string>
#include <iostream>
using namespace std;

class PrintHelper {

private:
	static int deep;

public:
	static void Enter() {
		deep++;
	}

	static void EnterPrint(string str) {
		deep++;
		Print(str);
	}

	static void Exit() {
		deep--;
	}

	static void ExitPrint(string str) {
		Print(str);
		deep--;
	}

	static void Print(string str) {
		for (int i = 0; i < deep; i++) {
			cout << "\t";
		}
		cout << str << endl;
	}

};

int PrintHelper::deep = -1;