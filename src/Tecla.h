#pragma once
#include <array>
#include <Windows.h>
#include <xinput.h>
class Tecla {
private:
	
	std::array<WORD,1>teclasCode;
public:
	Tecla();
	~Tecla();
	void setTecla(int pos,WORD code);
	WORD getTecla(int pos);
};