#pragma once
#include <string>

class Slots {
public:

	Slots(std::string name, std::string file);
	~Slots();
	std::string getName();
	std::string getFile();

private:

	std::string name;
	std::string saveFile;
};