#include <iostream>
#include <Windows.h>
#include <xinput.h>
void simulate(WORD virtualKey) {
	int x = 0;
	while (x == 0) {
		INPUT input;
		ZeroMemory(&input, sizeof(INPUT));
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = virtualKey;
		input.ki.dwFlags = 0;
		SendInput(1, &input, sizeof(INPUT));
		std::cout << "A" << std::endl;
		Sleep(100);
		input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));
		x = 1;
	}
}

void simulateMouse(WORD virtualKey) {
	int x = 0;
	while (x == 0) {
		INPUT input;
		ZeroMemory(&input, sizeof(INPUT));
		input.type = INPUT_MOUSE;
		input.ki.wVk = virtualKey;
		input.ki.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(INPUT));
		std::cout << "A" << std::endl;
		Sleep(100);
		input.ki.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(INPUT));
		x = 1;
	}
}
void simulateMovement(WORD virtualKey) {
	int x = 0;
	while (x == 0) {
		INPUT input;
		ZeroMemory(&input, sizeof(INPUT));
		input.type = INPUT_MOUSE;
		input.ki.wVk = virtualKey;
		input.ki.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(INPUT));
		std::cout << "A" << std::endl;
		Sleep(100);
		input.ki.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(INPUT));
		x = 1;
	}
}
int main() {
	int x = 0;
	while (true) {
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(0, &state);
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
			simulate(0x57);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
			simulate(0x41);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
			simulate(0x44);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			simulateMouse(0x01);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) {
			simulate(0x57);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) {
			simulate(0x44);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			simulate(0x41);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			simulate(0x44);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.sThumbLX)) {
			simulateMovement(0x44);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.sThumbLY)) {
			simulateMovement(0x44);
		}
		else {
			//simulate(VK_SPACE);
		}

	}
	return 0;
}