#include "Button.h"



Button::Button(std::string name, float x, float y,ControllerLayout button) {
	_buttonName = name;
	_posX = x;
	_posY = y;
	keyButton = button;
	_initialName = name;
}

Button::~Button() {

}

bool Button::GetWaiting() {
	return waitForInput;
}
void Button::SetWaiting(bool wait) {
	waitForInput = wait;
}

float Button::GetX() {
	return _posX;
}
float Button::GetY() {
	return _posY;
}
std::string Button::GetName() {
	return _buttonName;
}

void Button::SetName(std::string txt) {
	_buttonName = txt;
}
std::string Button::GetInitialName()
{
	return _initialName;
}
ControllerLayout Button::GetKey() {
	return keyButton;
}