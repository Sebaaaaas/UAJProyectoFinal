#pragma once
#include <string>

enum ControllerLayout;
class Button {
public:
	Button(std::string name, float x, float y, ControllerLayout button);
	~Button();
	bool GetWaiting();
	void SetWaiting(bool wait);
	float GetX();
	float GetY();
	std::string GetName();
	void SetName(std::string txt);
	std::string GetInitialName();

	ControllerLayout GetKey();

	void SetBackupName(std::string txt);
	std::string GetBackupName();
private:

	std::string buttonName;
	float posX;
	float posY;
	bool waitForInput = false;

	std::string initialName;
	ControllerLayout keyButton;

	std::string _backupname;
};