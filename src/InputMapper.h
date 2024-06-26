#pragma once

#include <vector>
#include <fstream>
#include "DefInput.h"

class InputMapper
{
public: 
	InputMapper();
	~InputMapper();
	void setButton(ControllerLayout button, KeyboardKey key);
	void resetButton(ControllerLayout button);
	KeyboardKey getKey(ControllerLayout button);
	void saveControls(bool checkL,bool checkR, const char * file);
	void loadControls(bool& checkL_, bool& checkR_, const char * file);
	std::vector<std::pair<KeyboardKey, ControllerLayout>>* getButtons();
	
private:
	ControllerSettings* contrSettings;
	std::vector<std::pair<KeyboardKey, ControllerLayout>>usedKeys;
	void checkKeyIsFree(KeyboardKey key);
	void processLoad(std::ifstream& inFile,std::string word,ControllerLayout button, bool& checkL_, bool& checkR_);
	void resetAll();

};

