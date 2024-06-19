#include "InputMapper.h"
#include <string>


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

void InputMapper::saveControls(bool checkL,bool checkR)
{
	std:: ofstream outFile("controles.txt");
	if (!outFile.is_open()) {
		std::cout << "Error al abrir el archivo para escribir" << std::endl;
		return;
	}
	// Botones
	outFile << "ButtonA : " << contrSettings->buttonA << std::endl;
	outFile << "ButtonB : " << contrSettings->buttonB << std::endl;
	outFile << "ButtonX : " << contrSettings->buttonX << std::endl;
	outFile << "ButtonY : " << contrSettings->buttonY << std::endl;

	// Dpad
	outFile << "dPadUp : " << contrSettings->dpadUp << std::endl;
	outFile << "dPadDown : " << contrSettings->dpadDown << std::endl;	
	outFile << "dPadRight : " << contrSettings->dpadRight << std::endl;
	outFile << "dPadLeft : " << contrSettings->dpadLeft << std::endl;

	// Joysticks
	outFile << "leftJoystick_left : " << contrSettings->leftJoystick_left << std::endl; 
	outFile << "leftJoystick_right : " << contrSettings->leftJoystick_right << std::endl;
	outFile << "leftJoystick_up : " << contrSettings->leftJoystick_up << std::endl;
	outFile << "leftJoystick_down : " << contrSettings->leftJoystick_down << std::endl;

	outFile << "rightJoystick_left : " << contrSettings->rightJoystick_left << std::endl;
	outFile << "rightJoystick_right : " << contrSettings->rightJoystick_right << std::endl;
	outFile << "rightJoystick_up : " << contrSettings->rightJoystick_up << std::endl;
	outFile << "rightJoystick_down : " << contrSettings->rightJoystick_down << std::endl;

	outFile << "leftJoystickButton : " << contrSettings->leftJoystickButton << std::endl;
	outFile << "rightJoystickButton : " << contrSettings->rightJoystickButton << std::endl;

	// Gatillos
	outFile << "LB : " << contrSettings->LB << std::endl;
	outFile << "RB : " << contrSettings->RB << std::endl;
	outFile << "LT : " << contrSettings->LT << std::endl;
	outFile << "RT : " << contrSettings->RT << std::endl;

	// Botones especiales
	outFile << "viewButton : " << contrSettings->viewButton << std::endl;
	outFile << "menuButton : " << contrSettings->menuButton << std::endl;

	outFile << "checkL : " << checkL << std::endl;
	outFile << "checkR : " << checkR << std::endl;
	outFile.close();
}

void InputMapper::loadControls(bool& checkL_, bool& checkR_)
{
	std::ifstream inFile("controles.txt");
	if (!inFile.is_open()) {
		std::cout << "Error al abrir el archivo para leer" << std::endl;
		
	}
	else {
		std::string word;
		while (inFile >> word) {
			if (word == "ButtonA") {
				processLoad(inFile, word, ButtonA, checkL_, checkR_);
			}
			else if (word == "ButtonB") {
				processLoad(inFile, word, ButtonB, checkL_, checkR_);
			}
			else if (word == "ButtonX") {
				processLoad(inFile, word, ButtonX, checkL_, checkR_);
			}
			else if (word == "ButtonY") {
				processLoad(inFile, word, ButtonY, checkL_, checkR_);
			}
			else if (word == "dPadUp") {
				processLoad(inFile, word, DpadUp, checkL_, checkR_);
			}
			else if (word == "dPadDown") {
				processLoad(inFile, word, DpadDown, checkL_, checkR_);
			}
			else if (word == "dPadRight") {
				processLoad(inFile, word, DpadRight, checkL_, checkR_);
			}
			else if (word == "dPadLeft") {
				processLoad(inFile, word, DpadLeft, checkL_, checkR_);
			}
			else if (word == "leftJoystick_left") {
				processLoad(inFile, word, LeftJoystickLeft, checkL_, checkR_);
			}
			else if (word == "leftJoystick_right") {
				processLoad(inFile, word, LeftJoystickRight, checkL_, checkR_);
			}
			else if (word == "leftJoystick_up") {
				processLoad(inFile, word, LeftJoystickUp, checkL_, checkR_);
			}
			else if (word == "leftJoystick_down") {
				processLoad(inFile, word, LeftJoystickDown, checkL_, checkR_);
			}
			else if (word == "rightJoystick_left") {
				processLoad(inFile, word, RightJoystickLeft, checkL_, checkR_);
			}
			else if (word == "rightJoystick_right") {
				processLoad(inFile, word, RightJoystickRight, checkL_, checkR_);
			}
			else if (word == "rightJoystick_up") {
				processLoad(inFile, word, RightJoystickUp, checkL_, checkR_);
			}
			else if (word == "rightJoystick_down") {
				processLoad(inFile, word, RightJoystickDown, checkL_, checkR_);
			}
			else if (word == "leftJoystickButton") {
				processLoad(inFile, word, LeftJoystickButton, checkL_, checkR_);
			}
			else if (word == "rightJoystickButton") {
				processLoad(inFile, word, RightJoystickButton, checkL_, checkR_);
			}
			else if (word == "LB") {
				processLoad(inFile, word, LB, checkL_, checkR_);
			}
			else if (word == "RB") {
				processLoad(inFile, word, RB, checkL_, checkR_);
			}
			else if (word == "LT") {
				processLoad(inFile, word, LT, checkL_, checkR_);
			}
			else if (word == "RT") {
				processLoad(inFile, word, RT, checkL_, checkR_);
			}
			else if (word == "viewButton") {
				processLoad(inFile, word, ViewButton,checkL_, checkR_);
			}
			else if (word == "menuButton") {
				processLoad(inFile, word, MenuButton,checkL_,checkR_);
			}
			else if (word == "checkL") {
				processLoad(inFile, word, MenuButton, checkL_, checkR_);
			}
			else if (word == "checkR") {
				processLoad(inFile, word, MenuButton, checkL_, checkR_);
			}
		}
		inFile.close();
	}
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

void InputMapper::processLoad(std::ifstream& inFile,std::string word, ControllerLayout button,bool& checkL_,bool& checkR_)
{
	if (word == "checkL") {
		inFile >> word;
		inFile >> word;
		checkL_ = std::stoi(word);
	}
	else if (word == "checkR") {
		inFile >> word;
		inFile >> word;
		checkR_ = std::stoi(word);
	}
	else {
		inFile >> word;
		inFile >> word;
		setButton(button, (KeyboardKey)std::stoi(word));
	}
}
