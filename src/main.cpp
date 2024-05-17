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

void simulateMouseClick() {
	INPUT input;
	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // Presiona el botón izquierdo del ratón
	SendInput(1, &input, sizeof(INPUT));
	//Sleep(50); // Espera un breve momento antes de soltar el botón
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // Suelta el botón izquierdo del ratón
	SendInput(1, &input, sizeof(INPUT));
}
void simulateMouseMove(short deltaX, short deltaY) {
	INPUT input;
	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;
	input.mi.dx = deltaX/ 3276; // Cambio horizontal del cursor
	input.mi.dy = -deltaY/ 3276; // Cambio vertical del cursor
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(INPUT));
}

int main() {
	int x = 0;
	while (true) {
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(0, &state);
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
			simulateMouseClick();
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
			std::cout << "X" << std::endl;
			simulate(0x41);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
			simulate(0x44);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			simulate(0x57);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) {
			simulate(0x57);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) {
			simulate(0x53);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
			simulate(0x41);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
			simulate(0x44);
		}
		if (result == ERROR_SUCCESS) {
			// Obtén los valores del joystick izquierdo
			short thumbRX = state.Gamepad.sThumbRX;
			short thumbRY = state.Gamepad.sThumbRY;

			// Verifica si el joystick izquierdo se está moviendo
			if (thumbRX != 0 || thumbRY != 0) {
				// Llama a una función para simular el movimiento del ratón
				simulateMouseMove(thumbRX, thumbRY);
			}
		}
		if (result == ERROR_SUCCESS) {
			// Obtén los valores del joystick izquierdo
			short thumbLX = state.Gamepad.sThumbLX;
			short thumbLY = state.Gamepad.sThumbLY;

			// Verifica si el joystick izquierdo se está moviendo
			if (thumbLX > 0) {
				// Llama a una función para simular el movimiento del ratón
				simulate(0x44);
			}
			else if (thumbLX < 0) {
				simulate(0x41);
			}
			if (thumbLY > 0) {
				simulate(0x57);
			}
			else if (thumbLY < 0) {
				simulate(0x53);
			}
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) { //Pulsar LB 
			simulate(0x45);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)) { //Pulsar joystick izquierdo
			simulate(0x41);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)) { //Pulsar RB 
			simulate(0x09);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) { //Pulsar joystick derecho
			simulate(0x41);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.bLeftTrigger)) { //Pulsar LT 
			if(state.Gamepad.bLeftTrigger > 75)
				simulate(0x45);
		}
		if (result == ERROR_SUCCESS && (state.Gamepad.bRightTrigger)) { //Pulsar RT
			if (state.Gamepad.bRightTrigger > 75)
				simulate(0x09);
		}

		

		
		else {
			//simulate(VK_SPACE);
		}
		Sleep(20);
	}
	return 0;
}