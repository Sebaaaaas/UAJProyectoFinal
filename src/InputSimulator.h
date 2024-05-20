#pragma once

#include "DefInput.h"

class InputMapper;
class InputSimulator
{
public: 
	InputSimulator();
	~InputSimulator();
	void update();
	void setMapper(InputMapper* mapper);
private:
	void simulateKey(KeyboardKey key);
	bool simulateMouseKey(KeyboardKey key);
	void simulateMouseMove(short deltaX, short deltaY);

	InputMapper* mapper;
};
