#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

bool isStringNumber(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] < '0' || str[i]>'9') {
			return false;
		}
	}
	return true;
}

int main() {
	//SetCursorPos(100, 400);

	int cps = 1;
	std::string in;
	bool is_not_number = true;
	while (is_not_number) {
		cout << "how many clicks per second?:";
		cin >> in;
		if (isStringNumber(in)) {
			is_not_number = false;
		}
		system("cls");
	}
	cps = stoi(in);
	cout << "clicking " << cps << " time(s) a second" << endl;

	bool rctrl_pressed = false;
	int sleep_time = 1000 / cps;
	int sleep = sleep_time;

	bool active = true;
	cout << "X: exit\nRight Control: toggle active state\nshift + Left Control: clicking\n";
	cout << "autoclicker: ACTIVE" << endl;

	while (true) {
		if (GetAsyncKeyState('X') & 0x8000)
			break;

		if (GetAsyncKeyState(VK_RCONTROL) < 0 && !rctrl_pressed)
		{
			rctrl_pressed = true;
		}
		if (GetAsyncKeyState(VK_RCONTROL) == 0 && rctrl_pressed) {
			rctrl_pressed = false;
			active = !active;
			if (active) {
				cout << "autoclicker: ACTIVE" << endl;
			}
			else {
				cout << "autoclicker: deactive" << endl;
			}
		}

		if (active && GetAsyncKeyState(VK_SHIFT) & 0x8000 && GetAsyncKeyState(VK_LCONTROL) & 0x8000)
		{
			sleep = sleep_time;
			mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		else {
			sleep = 10;
		}

		this_thread::sleep_for(chrono::milliseconds(sleep));
	}

	return 0;
}