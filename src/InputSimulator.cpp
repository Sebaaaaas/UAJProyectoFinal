#include "InputSimulator.h"
#include "InputMapper.h"
#include <Windows.h>
#include <xinput.h>

InputSimulator::InputSimulator()
{
	mapper = nullptr;
	pressedButtons = std::vector(numButtons, false);
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
	if (result != ERROR_SUCCESS)return;

	// Botones principales
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		simulateKeyPressed(mapper->getKey(ButtonY));
		pressedButtons[ButtonY] = true;
		
	}
	else if (pressedButtons[ButtonY]) {
		simulateKeyReleased(mapper->getKey(ButtonY));
		pressedButtons[ButtonY] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		simulateKeyPressed(mapper->getKey(ButtonX));
		pressedButtons[ButtonX] = true;
	}
	else if (pressedButtons[ButtonX]) {
		simulateKeyReleased(mapper->getKey(ButtonX));
		pressedButtons[ButtonX] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		simulateKeyPressed(mapper->getKey(ButtonA));
		pressedButtons[ButtonA] = true;
	}
	else if (pressedButtons[ButtonA]) {
		simulateKeyReleased(mapper->getKey(ButtonA));
		pressedButtons[ButtonA] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		simulateKeyPressed(mapper->getKey(ButtonB));
		pressedButtons[ButtonB] = true;
	}
	else if (pressedButtons[ButtonB]) {
		simulateKeyReleased(mapper->getKey(ButtonB));
		pressedButtons[ButtonB] = false;
	}

	// Dpad
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		simulateKeyPressed(mapper->getKey(DpadUp));
		pressedButtons[DpadUp] = true;
	}
	else if (pressedButtons[DpadUp]) {
		simulateKeyReleased(mapper->getKey(DpadUp));
		pressedButtons[DpadUp] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		simulateKeyPressed(mapper->getKey(DpadDown));
		pressedButtons[DpadDown] = true;
	}
	else if (pressedButtons[DpadDown]) {
		simulateKeyReleased(mapper->getKey(DpadDown));
		pressedButtons[DpadDown] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		simulateKeyPressed(mapper->getKey(DpadLeft));
		pressedButtons[DpadLeft] = true;
	}
	else if (pressedButtons[DpadLeft]) {
		simulateKeyReleased(mapper->getKey(DpadLeft));
		pressedButtons[DpadLeft] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		simulateKeyPressed(mapper->getKey(DpadRight));
		pressedButtons[DpadRight] = true;
	}
	else if (pressedButtons[DpadRight]) {
		simulateKeyReleased(mapper->getKey(DpadRight));
		pressedButtons[DpadRight] = false;
	}
	
	// Joysticks
	if (movRight) {
		// Obtén los valores del joystick derecho
		short thumbRX = state.Gamepad.sThumbRX;
		short thumbRY = state.Gamepad.sThumbRY;

		// Verifica si el joystick derecho se está moviendo
		if (abs(thumbRX) > joystickThreshold || abs(thumbRY) > joystickThreshold) {
			// Llama a una función para simular el movimiento del ratón
			simulateMouseMove(thumbRX, thumbRY);
		}
	}
	else {
		// Obtén los valores del joystick izquierdo
		short thumbRX = state.Gamepad.sThumbRX;
		short thumbRY = state.Gamepad.sThumbRY;

		// Verifica si el joystick izquierdo se está moviendo
		if (thumbRX > joystickThreshold) {
			simulateKeyPressed(mapper->getKey(RightJoystickRight));
			pressedButtons[RightJoystickRight] = true;
			
		}
		else if (pressedButtons[RightJoystickRight]) {
			simulateKeyReleased(mapper->getKey(RightJoystickRight));
			pressedButtons[RightJoystickRight] = false;
		}

		if (thumbRX < -joystickThreshold) {
			simulateKeyPressed(mapper->getKey(RightJoystickLeft));
			pressedButtons[RightJoystickLeft] = true;
		}
		else if (pressedButtons[RightJoystickLeft]) {
			simulateKeyReleased(mapper->getKey(RightJoystickLeft));
			pressedButtons[RightJoystickLeft] = false;
		}

		if (thumbRY > joystickThreshold) {
			simulateKeyPressed(mapper->getKey(RightJoystickUp));
			pressedButtons[RightJoystickUp] = true;

		}
		else if (pressedButtons[RightJoystickUp]) {
			simulateKeyReleased(mapper->getKey(RightJoystickUp));
			pressedButtons[RightJoystickUp] = false;
		}

		if (thumbRY < -joystickThreshold) {
			simulateKeyPressed(mapper->getKey(RightJoystickDown));
			pressedButtons[RightJoystickDown] = true;
		}
		else if (pressedButtons[RightJoystickDown]) {
			simulateKeyReleased(mapper->getKey(RightJoystickDown));
			pressedButtons[RightJoystickDown] = false;
		}
	}

	if (movLeft) {
		// Obtén los valores del joystick izquierdo
		short thumbLX = state.Gamepad.sThumbLX;
		short thumbLY = state.Gamepad.sThumbLY;

		// Verifica si el joystick izquierdo se está moviendo
		if (abs(thumbLX) > joystickThreshold || abs(thumbLY) > joystickThreshold) {
			// Llama a una función para simular el movimiento del ratón
			simulateMouseMove(thumbLX, thumbLY);
		}
	}
	else {
		// Obtén los valores del joystick izquierdo
		short thumbLX = state.Gamepad.sThumbLX;
		short thumbLY = state.Gamepad.sThumbLY;

		// Verifica si el joystick izquierdo se está moviendo
		if (thumbLX > joystickThreshold) {
			simulateKeyPressed(mapper->getKey(LeftJoystickRight));
			pressedButtons[LeftJoystickRight] = true;
		}
		else if (pressedButtons[LeftJoystickRight]) {
			simulateKeyReleased(mapper->getKey(LeftJoystickRight));
			pressedButtons[LeftJoystickRight] = false;
		}

		if (thumbLX < -joystickThreshold) {
			simulateKeyPressed(mapper->getKey(LeftJoystickLeft));
			pressedButtons[LeftJoystickLeft] = true;
		}
		else if (pressedButtons[LeftJoystickLeft]) {
			simulateKeyReleased(mapper->getKey(LeftJoystickLeft));
			pressedButtons[LeftJoystickLeft] = false;
		}

		if (thumbLY > joystickThreshold) {
			simulateKeyPressed(mapper->getKey(LeftJoystickUp));
			pressedButtons[LeftJoystickUp] = true;
		}
		else if (pressedButtons[LeftJoystickUp]) {
			simulateKeyReleased(mapper->getKey(LeftJoystickUp));
			pressedButtons[LeftJoystickUp] = false;
		}

		if (thumbLY < -joystickThreshold) {
			simulateKeyPressed(mapper->getKey(LeftJoystickDown));
			pressedButtons[LeftJoystickDown] = true;
		}
		else if (pressedButtons[LeftJoystickDown]) {
			simulateKeyReleased(mapper->getKey(LeftJoystickDown));
			pressedButtons[LeftJoystickDown] = false;
		}
	}

	// Gatillos, shoulders, botones de joysticks y demas botones
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) { //Pulsar LB 
		simulateKeyPressed(mapper->getKey(LB));
		pressedButtons[LB] = true;
	}
	else if (pressedButtons[LB]) {
		simulateKeyReleased(mapper->getKey(LB));
		pressedButtons[LB] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) { //Pulsar joystick izquierdo 
		simulateKeyPressed(mapper->getKey(LeftJoystickButton));
		pressedButtons[LeftJoystickButton] = true;
	}
	else if (pressedButtons[LeftJoystickButton]) {
		simulateKeyReleased(mapper->getKey(LeftJoystickButton));
		pressedButtons[LeftJoystickButton] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) { //Pulsar RB  
		simulateKeyPressed(mapper->getKey(RB));
		pressedButtons[RB] = true;
	}
	else if (pressedButtons[RB]) {
		simulateKeyReleased(mapper->getKey(RB));
		pressedButtons[RB] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) { //Pulsar joystick derecho 
		simulateKeyPressed(mapper->getKey(RightJoystickButton));
		pressedButtons[RightJoystickButton] = true;
	}
	else if (pressedButtons[RightJoystickButton]) {
		simulateKeyReleased(mapper->getKey(RightJoystickButton));
		pressedButtons[RightJoystickButton] = false;
	}

	if (state.Gamepad.bLeftTrigger && state.Gamepad.bLeftTrigger > 75) { //Pulsar LT 
		simulateKeyPressed(mapper->getKey(LT));
		pressedButtons[LT] = true;
	}
	else if (pressedButtons[LT]) {
		simulateKeyReleased(mapper->getKey(LT));
		pressedButtons[LT] = false;
	}

	if (state.Gamepad.bRightTrigger && state.Gamepad.bRightTrigger > 75) { //Pulsar RT 
		simulateKeyPressed(mapper->getKey(RT));
		pressedButtons[RT] = true;
	}
	else if (pressedButtons[RT]) {
		simulateKeyReleased(mapper->getKey(RT));
		pressedButtons[RT] = false;
	}
	
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) { //Pulsar boton menu
		simulateKeyPressed(mapper->getKey(MenuButton));
		pressedButtons[MenuButton] = true;
	}
	else if (pressedButtons[MenuButton]) {
		simulateKeyReleased(mapper->getKey(MenuButton));
		pressedButtons[MenuButton] = false;
	}

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) { //Pulsar boton view
		simulateKeyPressed(mapper->getKey(ViewButton));
		pressedButtons[ViewButton] = true;
	}
	else if (pressedButtons[ViewButton]) {
		simulateKeyReleased(mapper->getKey(ViewButton));
		pressedButtons[ViewButton] = false;
	}
}

void InputSimulator::setMapper(InputMapper* mapper)
{
	this->mapper = mapper;
}

void InputSimulator::simulateKeyPressed(KeyboardKey key)
{
	if (key == NONE)return;

	if (simulateMouseKeyPressed(key))return;

	INPUT input;
	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
}

void InputSimulator::simulateKeyReleased(KeyboardKey key)
{
	if (key == NONE)return;

	if (simulateMouseKeyReleased(key))return;

	INPUT input;
	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

bool InputSimulator::simulateMouseKeyPressed(KeyboardKey key)
{
	if (key == NONE || (key != KEY_MLCLICK && key != KEY_MRCLICK && key != KEY_MMIDDLEBUTTON))return false;

	INPUT input;
	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;

	if (key == KEY_MLCLICK)input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // Presiona el botón izquierdo del ratón
	else if (key == KEY_MRCLICK)input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; // Presiona el botón derecho del ratón
	else input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN; // Presiona el botón central del ratón

	SendInput(1, &input, sizeof(INPUT));
	return true;
}

bool InputSimulator::simulateMouseKeyReleased(KeyboardKey key)
{
	if (key == NONE || (key != KEY_MLCLICK && key != KEY_MRCLICK && key != KEY_MMIDDLEBUTTON))return false;

	INPUT input;
	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;

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

void InputSimulator::setLeftMovement(bool leftMov) {
	movLeft = leftMov;
}

void InputSimulator::setRightMovement(bool rightMov) {
	movRight = rightMov;
}
