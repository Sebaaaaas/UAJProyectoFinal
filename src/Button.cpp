#include "Button.h"
#include "InputMapper.h"

Button::Button(std::string name, float x, float y, ControllerLayout button) {
	buttonName = name;
	posX = x;
	posY = y;
	keyButton = button;
	initialName = name;
	_backupname = name;
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
	return posX;
}
float Button::GetY() {
	return posY;
}
std::string Button::GetName() {
	return buttonName;
}

void Button::SetName(std::string txt) {
	buttonName = txt;
}
std::string Button::GetInitialName()
{
	return initialName;
}
ControllerLayout Button::GetKey() {
	return keyButton;
}

void Button::SetBackupName(std::string txt) {
	_backupname = txt;
}
std::string Button::GetBackupName() {
	return _backupname;
}