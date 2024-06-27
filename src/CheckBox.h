#pragma once
#include <string>

class CheckBox {
public:

	CheckBox( float x, float y,std::string name);
	~CheckBox();
	float getX();
	float getY();

	std::string getName();

private:

	float posX;
	float posY;
	std::string name;
};