#include "Tecla.h"
Tecla::Tecla()
{
	teclasCode = std::array<WORD, 1>();
}
Tecla::~Tecla()
{
	
}
void Tecla::setTecla(int pos, WORD code)
{
	teclasCode[pos] = code;
}
WORD Tecla::getTecla(int pos) {
	return teclasCode[pos];
}

int Tecla::getTam()
{
	return teclasCode.size();
}
