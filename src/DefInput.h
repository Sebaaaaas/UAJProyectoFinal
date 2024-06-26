#pragma once

enum KeyboardKey {
	KEY_MLCLICK = 0x01, //click izquierdo del raton
	KEY_MRCLICK = 0x02, //click derecho del raton
	KEY_MMIDDLEBUTTON = 0x04, //click en la rueda del raton
	KEY_MX1BUTTON = 0x05, //Boton X1 del raton (estos botones son los que estan al lado del raton) 
	KEY_MX2BUTTON = 0x06, //Boton X2 del raton

	KEY_0 = 0x30,
	KEY_1 = 0x31,
	KEY_2 = 0x32,
	KEY_3 = 0x33,
	KEY_4 = 0x34,
	KEY_5 = 0x35,
	KEY_6 = 0x36,
	KEY_7 = 0x37,
	KEY_8 = 0x38,
	KEY_9 = 0x39,

	KEY_A = 0x41,
	KEY_B = 0x42,
	KEY_C = 0x43,
	KEY_D = 0x44,
	KEY_E = 0x45,
	KEY_F = 0x46,
	KEY_G = 0x47,
	KEY_H = 0x48,
	KEY_I = 0x49,
	KEY_J = 0x4A,
	KEY_K = 0x4B,
	KEY_L = 0x4C,
	KEY_M = 0x4D,
	KEY_N = 0x4E,
	KEY_O = 0x4F,
	KEY_P = 0x50,
	KEY_Q = 0x51,
	KEY_R = 0x52,
	KEY_S = 0x53,
	KEY_T = 0x54,
	KEY_U = 0x55,
	KEY_V = 0x56,
	KEY_W = 0x57,
	KEY_X = 0x58,
	KEY_Y = 0x59,
	KEY_Z = 0x5A,

	KEY_BACKSPACE = 0x08,
	KEY_TAB = 0x09,
	KEY_CLEAR = 0x0C,
	KEY_ENTER = 0x0D,
	
	KEY_SHIFT = 0x10,
	KEY_LSHIFT = 0xA0,
	KEY_RSHIFT = 0xA1,
	
	KEY_CONTROL = 0x11,
	KEY_LCONTROL = 0xA2,
	KEY_RCONTROL = 0xA3,
	
	KEY_ALT = 0x12,
	KEY_LALT = 0xA4,
	KEY_RALT = 0xA5,

	KEY_CAPSLOCK = 0x14,
	KEY_ESC = 0x1B,
	KEY_SPACE = 0x20,
	KEY_PAGEUP = 0x21,
	KEY_PAGEDOWN = 0x22,
	KEY_END = 0x23,
	KEY_HOME = 0x24,

	KEY_LEFTARROW = 0x25,
	KEY_UPARROW = 0x26,
	KEY_RIGHTARROW = 0x27,
	KEY_DOWNARROW = 0x28,

	KEY_NUMPAD0 = 0x60,
	KEY_NUMPAD1 = 0x61,
	KEY_NUMPAD2 = 0x62,
	KEY_NUMPAD3 = 0x63,
	KEY_NUMPAD4 = 0x64,
	KEY_NUMPAD5 = 0x65,
	KEY_NUMPAD6 = 0x66,
	KEY_NUMPAD7 = 0x67,
	KEY_NUMPAD8 = 0x68,
	KEY_NUMPAD9 = 0x69,
	KEY_NUMPADMULTIPLY = 0x6A,
	KEY_NUMPADADD = 0x6B,
	KEY_NUMPADSUBSTRACT = 0x6D,
	KEY_NUMPADDECIMAL = 0x6E,
	KEY_NUMPADDIVIDE = 0x6F,

	KEY_F1 = 0x70,
	KEY_F2 = 0x71,
	KEY_F3 = 0x72,
	KEY_F4 = 0x73,
	KEY_F5 = 0x74,
	KEY_F6 = 0x75,
	KEY_F7 = 0x76,
	KEY_F8 = 0x77,
	KEY_F9 = 0x78,
	KEY_F10 = 0x79,
	KEY_F11 = 0x7A,
	KEY_F12 = 0x7B,

	KEY_NUMLOCK = 0x90,

	KEY_PLUS = 0xBB,
	KEY_COMMA = 0xBC,
	KEY_MINUS = 0xBD,
	KEY_PERIOD = 0xBE,

	NONE = 0 // valor por defecto

};

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
	LeftJoystickDown,
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
	ViewButton, MenuButton,
	NotAKey

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