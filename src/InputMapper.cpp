#include "InputMapper.h"
#include <iostream>

InputMapper::InputMapper()
{
	contrSettings = new ControllerSettings();
}

InputMapper::~InputMapper()
{
}

void InputMapper::setButton(ControllerLayout button, KeyboardKey key)
{
	if (contrSettings == nullptr)return;

	checkKeyIsFree(key);
	switch (button)
	{
	case ButtonA:
		contrSettings->buttonA = key;
		usedKeys.push_back({ key,ButtonA });
		break;
	case ButtonB:
		contrSettings->buttonB = key;
		usedKeys.push_back({ key,ButtonB });
		break;
	case ButtonX:
		contrSettings->buttonX = key;
		usedKeys.push_back({ key,ButtonX });
		break;
	case ButtonY:
		contrSettings->buttonY = key;
		usedKeys.push_back({ key,ButtonY });
		break;
	case DpadUp:
		contrSettings->dpadUp = key;
		usedKeys.push_back({ key,DpadUp });
		break;
	case DpadDown:
		contrSettings->dpadDown = key;
		usedKeys.push_back({ key,DpadDown });
		break;
	case DpadRight:
		contrSettings->dpadRight = key;
		usedKeys.push_back({ key,DpadRight });
		break;
	case DpadLeft:
		contrSettings->dpadLeft = key;
		usedKeys.push_back({ key,DpadLeft });
		break;
	case LeftJoystickLeft:
		contrSettings->leftJoystick_left = key;
		usedKeys.push_back({ key,LeftJoystickLeft });
		break;
	case LeftJoystickRight:
		contrSettings->leftJoystick_right = key;
		usedKeys.push_back({ key,LeftJoystickRight });
		break;
	case LeftJoystickUp:
		contrSettings->leftJoystick_up = key;
		usedKeys.push_back({ key,LeftJoystickUp });
		break;
	case LeftJoystickDown:
		contrSettings->leftJoystick_down = key;
		usedKeys.push_back({ key,LeftJoystickDown });
		break;
	case RightJoystickLeft:
		contrSettings->rightJoystick_left = key;
		usedKeys.push_back({ key,RightJoystickLeft });
		break;
	case RightJoystickRight:
		contrSettings->rightJoystick_right = key;
		usedKeys.push_back({ key,RightJoystickRight });
		break;
	case RightJoystickUp:
		contrSettings->rightJoystick_up = key;
		usedKeys.push_back({ key,RightJoystickUp });
		break;
	case RightJoystickDown:
		contrSettings->rightJoystick_down = key;
		usedKeys.push_back({ key,RightJoystickDown });
		break;
	case LeftJoystickButton:
		contrSettings->leftJoystickButton = key;
		usedKeys.push_back({ key,LeftJoystickButton });
		break;
	case RightJoystickButton:
		contrSettings->rightJoystickButton = key;
		usedKeys.push_back({ key,RightJoystickButton });
		break;
	case LB:
		contrSettings->LB = key;
		usedKeys.push_back({ key,LB });
		break;
	case RB:
		contrSettings->RB = key;
		usedKeys.push_back({ key,RB });
		break;
	case LT:
		contrSettings->LT = key;
		usedKeys.push_back({ key,LT });
		break;
	case RT:
		contrSettings->RT = key;
		usedKeys.push_back({ key,RT });
		break;
	case ViewButton:
		contrSettings->viewButton = key;
		usedKeys.push_back({ key,ViewButton });
		break;
	case MenuButton:
		contrSettings->menuButton = key;
		usedKeys.push_back({ key,MenuButton });
		break;
	default:
		break;
	}
}

void InputMapper::resetButton(ControllerLayout button)
{
	if (contrSettings == nullptr)return;
	switch (button)
	{
	case ButtonA:
		contrSettings->buttonA = NONE;
		break;
	case ButtonB:
		contrSettings->buttonB = NONE;
		break;
	case ButtonX:
		contrSettings->buttonX = NONE;
		break;
	case ButtonY:
		contrSettings->buttonY = NONE;
		break;
	case DpadUp:
		contrSettings->dpadUp = NONE;
		break;
	case DpadDown:
		contrSettings->dpadDown = NONE;
		break;
	case DpadRight:
		contrSettings->dpadRight = NONE;
		break;
	case DpadLeft:
		contrSettings->dpadLeft = NONE;
		break;
	case LeftJoystickLeft:
		contrSettings->leftJoystick_left = NONE;
		break;
	case LeftJoystickRight:
		contrSettings->leftJoystick_right = NONE;
		break;
	case LeftJoystickUp:
		contrSettings->leftJoystick_up = NONE;
		break;
	case LeftJoystickDown:
		contrSettings->leftJoystick_down = NONE;
		break;
	case RightJoystickLeft:
		contrSettings->rightJoystick_left = NONE;
		break;
	case RightJoystickRight:
		contrSettings->rightJoystick_right = NONE;
		break;
	case RightJoystickUp:
		contrSettings->rightJoystick_up = NONE;
		break;
	case RightJoystickDown:
		contrSettings->rightJoystick_down = NONE;
		break;
	case LeftJoystickButton:
		contrSettings->leftJoystickButton = NONE;
		break;
	case RightJoystickButton:
		contrSettings->rightJoystickButton = NONE;
		break;
	case LB:
		contrSettings->LB = NONE;
		break;
	case RB:
		contrSettings->RB = NONE;
		break;
	case LT:
		contrSettings->LT = NONE;
		break;
	case RT:
		contrSettings->RT = NONE;
		break;
	case ViewButton:
		contrSettings->viewButton = NONE;
		break;
	case MenuButton:
		contrSettings->menuButton = NONE;
		break;
	default:
		break;
	}
}

KeyboardKey InputMapper::getKey(ControllerLayout button)
{
	if (contrSettings == nullptr)return NONE;
	switch (button)
	{
	case ButtonA:
		return contrSettings->buttonA;
		break;
	case ButtonB:
		return contrSettings->buttonB;
		break;
	case ButtonX:
		return contrSettings->buttonX;
		break;
	case ButtonY:
		return contrSettings->buttonY;
		break;
	case DpadUp:
		return contrSettings->dpadUp;
		break;
	case DpadDown:
		return contrSettings->dpadDown;
		break;
	case DpadRight:
		return contrSettings->dpadRight;
		break;
	case DpadLeft:
		return contrSettings->dpadLeft;
		break;
	case LeftJoystickLeft:
		return contrSettings->leftJoystick_left;
		break;
	case LeftJoystickRight:
		return contrSettings->leftJoystick_right;
		break;
	case LeftJoystickUp:
		return contrSettings->leftJoystick_up;
		break;
	case LeftJoystickDown:
		return contrSettings->leftJoystick_down;
		break;
	case RightJoystickLeft:
		return contrSettings->rightJoystick_left;
		break;
	case RightJoystickRight:
		return contrSettings->rightJoystick_right;
		break;
	case RightJoystickUp:
		return contrSettings->rightJoystick_up;
		break;
	case RightJoystickDown:
		return contrSettings->rightJoystick_down;
		break;
	case LeftJoystickButton:
		return contrSettings->leftJoystickButton;
		break;
	case RightJoystickButton:
		return contrSettings->rightJoystickButton;
		break;
	case LB:
		return contrSettings->LB;
		break;
	case RB:
		return contrSettings->RB;
		break;
	case LT:
		return contrSettings->LT;
		break;
	case RT:
		return contrSettings->RT;
		break;
	case ViewButton:
		return contrSettings->viewButton;
		break;
	case MenuButton:
		return contrSettings->menuButton;
		break;
	default:
		break;
	}
	return NONE;
}

void InputMapper::checkKeyIsFree(KeyboardKey key)
{
	int it = 0;
	for (auto e : usedKeys) {
		if (e.first == key) {
			resetButton(e.second);
			usedKeys.erase(usedKeys.begin() + it);
			return;
		}
		it++;
	}
}
