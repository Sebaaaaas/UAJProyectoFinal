#include "CheckBox.h"

CheckBox::CheckBox( float x, float y,std::string name) {
	posX = x;
	posY = y;
	this->name = name;
}

CheckBox::~CheckBox() {

}

float CheckBox::GetX() {
	return posX;
}

float CheckBox::GetY() {
	return posY;
}

std::string CheckBox::GetName() {
	return name;
}
