#include "Slots.h"

Slots::Slots(std::string name, std::string file)
{
	this->name = name;
	this->saveFile = file;

}

Slots::~Slots()
{
}

std::string Slots::GetName()
{
	return name;
}

std::string Slots::GetFile()
{
	return saveFile;
}
