#pragma once
#include <string>

class CheckBox {
public:

	CheckBox( float x, float y,std::string name);
	~CheckBox();
	float GetX();
	float GetY();

	std::string GetName();

private:

	float posX;
	float posY;
	std::string name;
};