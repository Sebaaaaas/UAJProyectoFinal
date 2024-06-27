#include "CheckBox.h"

CheckBox::CheckBox( float x, float y,std::string name) {
	posX = x;
	posY = y;
	this->name = name;
}

CheckBox::~CheckBox() {

}

float CheckBox::getX() {
	return posX;
}

float CheckBox::getY() {
	return posY;
}

std::string CheckBox::getName() {
	return name;
}
