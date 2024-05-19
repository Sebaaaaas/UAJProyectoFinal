#pragma once

#include "DefInput.h"
#include <vector>

enum ControllerLayout {
	ButtonA, ButtonB, ButtonX, ButtonY,
	DpadUp, DpadDown, DpadRight, DpadLeft,

	// Inclinar a la izquierda el joystick izquierdo
	LeftJoystickLeft, 
	// Inclinar a la derecha el joystick izquierdo
	LeftJoystickRight, 
	// Inclinar hacia arriba el joystick izquierdo
	LeftJoystickUp, 
	// Inclinar hacia abajo el joystick izquierdo
	LetfJoystickDown,
	// Inclinar a la izquierda el joystick derecho
	RightJoystickLeft,
	// Inclinar a la derecha el joystick derecho
	RightJoystickRight, 
	// Inclinar hacia arriba el joystick derecho
	RightJoystickUp, 
	// Inclinar hacia abajo el joystick derecho
	RightJoystickDown,
	// Presionar el boton del joystick izquierdo
	LeftJoystickButton, 
	// Presionar el boton del joystick derecho
	RightJoystickButton,

	LB, RB, LT, RT,
	ViewButton, MenuButton

};
struct ControllerSettings
{
	// Botones
	KeyboardKey buttonA = NONE;
	KeyboardKey buttonB = NONE;
	KeyboardKey buttonX = NONE;
	KeyboardKey buttonY = NONE;

	// Dpad
	KeyboardKey dpadUp = NONE;
	KeyboardKey dpadDown = NONE;
	KeyboardKey dpadRight = NONE;
	KeyboardKey dpadLeft = NONE;

	// Joysticks
	KeyboardKey leftJoystick_left = NONE; // asignacion joystick izq inclinado a la izq
	KeyboardKey leftJoystick_right = NONE; // asignacion joystick izq inclinado a la der
	KeyboardKey leftJoystick_up = NONE; // asignacion joystick izq inclinado hacia arriba
	KeyboardKey leftJoystick_down = NONE; // asignacion joystick izq inclinado hacia abajo

	KeyboardKey rightJoystick_left = NONE; // asignacion joystick der inclinado a la izq
	KeyboardKey rightJoystick_right = NONE; // asignacion joystick der inclinado a la der
	KeyboardKey rightJoystick_up = NONE; // asignacion joystick der inclinado hacia arriba
	KeyboardKey rightJoystick_down = NONE; // asignacion joystick der inclinado hacia abajo

	KeyboardKey leftJoystickButton = NONE; // pulsar el joystick izq
	KeyboardKey rightJoystickButton = NONE; // pulsar el joystick der

	// Gatillos
	KeyboardKey LB = NONE;
	KeyboardKey RB = NONE;
	KeyboardKey LT = NONE;
	KeyboardKey RT = NONE;

	// Botones especiales
	KeyboardKey viewButton = NONE;
	KeyboardKey menuButton = NONE;

};

class InputMapper
{
public: 
	InputMapper();
	~InputMapper();
	void setButton(ControllerLayout button, KeyboardKey key);
	void resetButton(ControllerLayout button);
private:
	ControllerSettings* contrSettings;
	std::vector<std::pair<KeyboardKey, ControllerLayout>>usedKeys;
	void checkKeyIsFree(KeyboardKey key);
};

