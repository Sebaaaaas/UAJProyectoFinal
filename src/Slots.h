#pragma once
#include <string>

class Slots {
public:

	Slots(std::string name, std::string file);
	~Slots();
	std::string GetName();
	std::string GetFile();

private:

	std::string _name;
	std::string _saveFile;
};