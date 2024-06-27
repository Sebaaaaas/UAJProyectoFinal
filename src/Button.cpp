#include "Button.h"
#include "InputMapper.h"

Button::Button(std::string name, float x, float y, ControllerLayout button) {
	buttonName = name;
	posX = x;
	posY = y;
	keyButton = button;
	initialName = name;
	backupname = name;
}

Button::~Button() {

}

bool Button::getWaiting() {
	return waitForInput;
}
void Button::setWaiting(bool wait) {
	waitForInput = wait;
}

float Button::getX() {
	return posX;
}
float Button::getY() {
	return posY;
}
std::string Button::getName() {
	return buttonName;
}

void Button::setName(std::string txt) {
	buttonName = txt;
}
std::string Button::getInitialName()
{
	return initialName;
}
ControllerLayout Button::getKey() {
	return keyButton;
}

void Button::setBackupName(std::string txt) {
	backupname = txt;
}
std::string Button::getBackupName() {
	return backupname;
}