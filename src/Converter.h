#pragma once

#include "DefInput.h"

enum ImGuiKey;
class Converter {
public:
	Converter(){}
	~Converter(){}
	KeyboardKey convertInput(ImGuiKey key);
	ImGuiKey convertToImGUiKey(KeyboardKey key);
};

