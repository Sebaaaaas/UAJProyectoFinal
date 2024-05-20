#include "InputSimulator.h"
#include "InputMapper.h"
#include <iostream>
#include <Windows.h>
#include <xinput.h>

InputSimulator::InputSimulator()
{
	mapper = nullptr;
}

InputSimulator::~InputSimulator()
{
}

void InputSimulator::update()
{
	if (mapper == nullptr)return;

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(0, &state);
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)) {
		simulateKey(mapper->getKey(ButtonY));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)) {
		simulateKey(mapper->getKey(ButtonX));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) {
		simulateKey(mapper->getKey(ButtonB));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
		simulateKey(mapper->getKey(ButtonA));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) {
		simulateKey(mapper->getKey(DpadUp));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) {
		simulateKey(mapper->getKey(DpadDown));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
		simulateKey(mapper->getKey(DpadLeft));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
		simulateKey(mapper->getKey(DpadRight));
	}
	if (result == ERROR_SUCCESS) {
		// Obtén los valores del joystick derecho
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
			simulateKey(mapper->getKey(LeftJoystickRight));
		}
		else if (thumbLX < 0) {
			simulateKey(mapper->getKey(LeftJoystickLeft));
		}
		if (thumbLY > 0) {
			simulateKey(mapper->getKey(LeftJoystickUp));
		}
		else if (thumbLY < 0) {
			simulateKey(mapper->getKey(LeftJoystickDown));
		}
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)) { //Pulsar LB 
		simulateKey(mapper->getKey(LB));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)) { //Pulsar joystick izquierdo
		simulateKey(mapper->getKey(LeftJoystickButton));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)) { //Pulsar RB 
		simulateKey(mapper->getKey(RB));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)) { //Pulsar joystick derecho
		simulateKey(mapper->getKey(RightJoystickButton));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.bLeftTrigger)) { //Pulsar LT 
		if (state.Gamepad.bLeftTrigger > 75)
			simulateKey(mapper->getKey(LT));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.bRightTrigger)) { //Pulsar RT
		if (state.Gamepad.bRightTrigger > 75)
			simulateKey(mapper->getKey(RT));
	}

	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)) { //Pulsar joystick derecho
		simulateKey(mapper->getKey(MenuButton));
	}
	if (result == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)) { //Pulsar joystick derecho
		simulateKey(mapper->getKey(ViewButton));
	}



	else {
		//simulate(VK_SPACE);
	}
}

void InputSimulator::setMapper(InputMapper* mapper)
{
	this->mapper = mapper;
}

void InputSimulator::simulateKey(KeyboardKey key)
{
	if (key == NONE)return;

	if (simulateMouseKey(key))return;

	INPUT input;
	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
	Sleep(100);
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

bool InputSimulator::simulateMouseKey(KeyboardKey key)
{
	if (key == NONE || (key != KEY_MLCLICK && key != KEY_MRCLICK && key != KEY_MMIDDLEBUTTON))return false;

	INPUT input;
	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;

	if (key == KEY_MLCLICK)input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // Presiona el botón izquierdo del ratón
	else if (key == KEY_MRCLICK)input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; // Presiona el botón derecho del ratón
	else input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN; // Presiona el botón central del ratón

	SendInput(1, &input, sizeof(INPUT));

	if (key == KEY_MLCLICK)input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // Suelta el botón izquierdo del ratón
	else if (key == KEY_MRCLICK)input.mi.dwFlags = MOUSEEVENTF_RIGHTUP; // Suelta el botón derecho del ratón
	else input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP; // Suelta el botón central del ratón

	SendInput(1, &input, sizeof(INPUT));
	return true;
}

void InputSimulator::simulateMouseMove(short deltaX, short deltaY)
{
	INPUT input;
	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;
	input.mi.dx = deltaX / 3276; // Cambio horizontal del cursor
	input.mi.dy = -deltaY / 3276; // Cambio vertical del cursor
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(INPUT));
}


