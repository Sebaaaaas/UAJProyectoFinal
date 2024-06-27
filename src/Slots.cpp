#include "Slots.h"

Slots::Slots(std::string name, std::string file)
{
	this->name = name;
	this->saveFile = file;

}

Slots::~Slots()
{
}

std::string Slots::getName()
{
	return name;
}

std::string Slots::getFile()
{
	return saveFile;
}
