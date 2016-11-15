#pragma once

#include <string>
#include <iostream>
using namespace std;

class PrintHelper {

private:
	static int deep;
	static bool show;

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
		if (show) {
			for (int i = 0; i < deep; i++) {
				cout << "\t";
			}
			cout << str << endl;
		}
	}

	static void Close() {
		show = false;
	}

	static void Open() {
		show = true;
	}

};