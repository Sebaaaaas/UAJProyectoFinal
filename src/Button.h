#pragma once
#include <string>

enum ControllerLayout;
class Button {
public:
	Button(std::string name, float x, float y, ControllerLayout button);
	~Button();
	bool getWaiting();
	void setWaiting(bool wait);
	float getX();
	float getY();
	std::string getName();
	void setName(std::string txt);
	std::string getInitialName();

	ControllerLayout getKey();

	void setBackupName(std::string txt);
	std::string getBackupName();
private:

	std::string buttonName;
	float posX;
	float posY;
	bool waitForInput = false;

	std::string initialName;
	ControllerLayout keyButton;

	std::string backupname;
};