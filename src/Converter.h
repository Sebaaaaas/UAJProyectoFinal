#pragma once

#include "DefInput.h"
#include <imgui.h>

class Converter {
public:
	Converter(){}
	~Converter(){}
	KeyboardKey convertInput(ImGuiKey key);
};

