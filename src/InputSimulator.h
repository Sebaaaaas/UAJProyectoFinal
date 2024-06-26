#pragma once

#include "DefInput.h"
#include <vector>

class InputMapper;
class InputSimulator
{
public: 
	InputSimulator();
	~InputSimulator();
	void update();
	void setMapper(InputMapper* mapper);
	void setLeftMovement(bool leftMov);
	void setRightMovement(bool rightMov);
	bool getPressed(int cb);
	// Numero de botones del mando que se pueden simular
	const int numButtons = 24;
private:
	void simulateKeyPressed(KeyboardKey key);
	void simulateKeyReleased(KeyboardKey key);
	bool simulateMouseKeyPressed(KeyboardKey key);
	bool simulateMouseKeyReleased(KeyboardKey key);
	void simulateMouseMove(short deltaX, short deltaY);


	InputMapper* mapper;
	bool movRight = false;
	bool movLeft = false;
	const short joystickThreshold = 10000;

	
	
	std::vector<bool>pressedButtons;
};

