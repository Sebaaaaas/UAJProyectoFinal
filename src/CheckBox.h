#pragma once
#include <string>

class CheckBox {
public:

	CheckBox( float x, float y);
	~CheckBox();
	float GetX();
	float GetY();

private:

	float _posX;
	float _posY;
};