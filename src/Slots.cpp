#include "Slots.h"

Slots::Slots(std::string name, std::string file)
{
	_name = name;
	_saveFile = file;

}

std::string Slots::GetName()
{
	return _name;
}

std::string Slots::GetFile()
{
	return _saveFile;
}
