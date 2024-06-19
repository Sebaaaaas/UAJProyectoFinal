#include "CheckBox.h"



CheckBox::CheckBox( float x, float y) {
	_posX = x;
	_posY = y;
}

CheckBox::~CheckBox() {

}

float CheckBox::GetX() {
	return _posX;
}

float CheckBox::GetY() {
	return _posY;
}
