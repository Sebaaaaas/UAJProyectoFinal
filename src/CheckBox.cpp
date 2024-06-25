#include "CheckBox.h"

CheckBox::CheckBox( float x, float y,std::string name) {
	_posX = x;
	_posY = y;
	_name = name;
}

CheckBox::~CheckBox() {

}

float CheckBox::GetX() {
	return _posX;
}

float CheckBox::GetY() {
	return _posY;
}

std::string CheckBox::GetName() {
	return _name;
}
