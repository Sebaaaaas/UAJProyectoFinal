#pragma once
#include <string>
#include "InputMapper.h"

class Button {
public:
	Button(std::string name,float x,float y,ControllerLayout button);
	~Button();
	bool GetWaiting();
	void SetWaiting(bool wait);
	float GetX();
	float GetY();
	std::string GetName();
	void SetName(std::string txt);

	ControllerLayout GetKey();
private:

	std::string _buttonName;
	float _posX;
	float _posY;
	bool waitForInput = false;
	ControllerLayout keyButton = MenuButton;
};