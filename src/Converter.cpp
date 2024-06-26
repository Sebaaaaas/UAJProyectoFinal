#include "Converter.h"
#include <imgui.h>

KeyboardKey Converter::convertInput(ImGuiKey key)
{
	switch (key) {
	case ImGuiKey_Space:
		return KEY_SPACE;
		break;

	case ImGuiKey_LeftArrow:
		return KEY_LEFTARROW;
		break;

	case ImGuiKey_UpArrow:
		return KEY_UPARROW;
		break;

	case ImGuiKey_RightArrow:
		return KEY_RIGHTARROW;
		break;

	case ImGuiKey_DownArrow:
		return KEY_DOWNARROW;
		break;

	case ImGuiKey_0:
		return KEY_0;
		break;

	case ImGuiKey_1:
		return KEY_1;
		break;

	case ImGuiKey_2:
		return KEY_2;
		break;

	case ImGuiKey_3:
		return KEY_3;
		break;

	case ImGuiKey_4:
		return KEY_4;
		break;

	case ImGuiKey_5:
		return KEY_5;
		break;

	case ImGuiKey_6:
		return KEY_6;
		break;

	case ImGuiKey_7:
		return KEY_7;
		break;

	case ImGuiKey_8:
		return KEY_8;
		break;

	case ImGuiKey_9:
		return KEY_9;
		break;

	case ImGuiKey_A:
		return KEY_A;
		break;

	case ImGuiKey_B:
		return KEY_B;
		break;

	case ImGuiKey_C:
		return KEY_C;
		break;

	case ImGuiKey_D:
		return KEY_D;
		break;

	case ImGuiKey_E:
		return KEY_E;
		break;

	case ImGuiKey_F:
		return KEY_F;
		break;

	case ImGuiKey_G:
		return KEY_G;
		break;

	case ImGuiKey_H:
		return KEY_H;
		break;

	case ImGuiKey_I:
		return KEY_I;
		break;

	case ImGuiKey_J:
		return KEY_J;
		break;

	case ImGuiKey_K:
		return KEY_K;
		break;

	case ImGuiKey_L:
		return KEY_L;
		break;

	case ImGuiKey_M:
		return KEY_M;
		break;

	case ImGuiKey_N:
		return KEY_N;
		break;

	case ImGuiKey_O:
		return KEY_O;
		break;

	case ImGuiKey_P:
		return KEY_P;
		break;

	case ImGuiKey_Q:
		return KEY_Q;
		break;

	case ImGuiKey_R:
		return KEY_R;
		break;

	case ImGuiKey_S:
		return KEY_S;
		break;

	case ImGuiKey_T:
		return KEY_T;
		break;

	case ImGuiKey_U:
		return KEY_U;
		break;

	case ImGuiKey_V:
		return KEY_V;
		break;

	case ImGuiKey_W:
		return KEY_W;
		break;

	case ImGuiKey_X:
		return KEY_X;
		break;

	case ImGuiKey_Y:
		return KEY_Y;
		break;

	case ImGuiKey_Z:
		return KEY_Z;
		break;

	case ImGuiKey_F1:
		return KEY_F1;
		break;

	case ImGuiKey_F2:
		return KEY_F2;
		break;

	case ImGuiKey_F3:
		return KEY_F3;
		break;

	case ImGuiKey_F4:
		return KEY_F4;
		break;

	case ImGuiKey_F5:
		return KEY_F5;
		break;

	case ImGuiKey_F6:
		return KEY_F6;
		break;

	case ImGuiKey_F7:
		return KEY_F7;
		break;

	case ImGuiKey_F8:
		return KEY_F8;
		break;

	case ImGuiKey_F9:
		return KEY_F9;
		break;

	case ImGuiKey_F10:
		return KEY_F10;
		break;

	case ImGuiKey_F11:
		return KEY_F11;
		break;

	case ImGuiKey_F12:
		return KEY_F12;
		break;

	case ImGuiKey_LeftShift:
		return KEY_SHIFT;
		break;

	case ImGuiKey_RightShift:
		return KEY_RSHIFT;
		break;

	case ImGuiKey_LeftCtrl:
		return KEY_CONTROL;
		break;

	case ImGuiKey_RightCtrl:
		return KEY_RCONTROL;
		break;

	case ImGuiKey_LeftAlt:
		return KEY_ALT;
		break;

	case ImGuiKey_Tab:
		return KEY_TAB;
		break;

	case ImGuiKey_Enter:
		return KEY_ENTER;
		break;

	case ImGuiKey_Backspace:
		return KEY_BACKSPACE;
		break;

	case ImGuiKey_MouseLeft:
		return KEY_MLCLICK;
		break;

	case ImGuiKey_MouseRight:
		return KEY_MRCLICK;
		break;

	case ImGuiKey_MouseMiddle:
		return KEY_MMIDDLEBUTTON;
		break;

	case ImGuiKey_Equal:  //es el +
		return KEY_PLUS;
		break;

	case ImGuiKey_Minus:
		return KEY_MINUS;
		break;

	case ImGuiKey_Period:
		return KEY_PERIOD;
		break;

	case ImGuiKey_Comma:
		return KEY_COMMA;
		break;

	default:
		return NONE;
	}

}

ImGuiKey Converter::convertToImGUiKey(KeyboardKey key)
{
	switch (key) {
	case KEY_SPACE:
		return ImGuiKey_Space;
		break;

	case KEY_LEFTARROW:
		return ImGuiKey_LeftArrow;
		break;

	case KEY_UPARROW:
		return ImGuiKey_UpArrow;
		break;

	case KEY_RIGHTARROW:
		return ImGuiKey_RightArrow;
		break;

	case KEY_DOWNARROW:
		return ImGuiKey_DownArrow;
		break;

	case KEY_0:
		return ImGuiKey_0;
		break;

	case KEY_1:
		return ImGuiKey_1;
		break;

	case KEY_2:
		return ImGuiKey_2;
		break;

	case KEY_3:
		return ImGuiKey_3;
		break;

	case KEY_4:
		return ImGuiKey_4;
		break;

	case KEY_5:
		return ImGuiKey_5;
		break;

	case KEY_6:
		return ImGuiKey_6;
		break;

	case KEY_7:
		return ImGuiKey_7;
		break;

	case KEY_8:
		return ImGuiKey_8;
		break;

	case KEY_9:
		return ImGuiKey_9;
		break;

	case KEY_A:
		return ImGuiKey_A;
		break;

	case KEY_B:
		return ImGuiKey_B;
		break;

	case KEY_C:
		return ImGuiKey_C;
		break;

	case KEY_D:
		return ImGuiKey_D;
		break;

	case KEY_E:
		return ImGuiKey_E;
		break;

	case KEY_F:
		return ImGuiKey_F;
		break;

	case KEY_G:
		return ImGuiKey_G;
		break;

	case KEY_H:
		return ImGuiKey_H;
		break;

	case KEY_I:
		return ImGuiKey_I;
		break;

	case KEY_J:
		return ImGuiKey_J;
		break;

	case KEY_K:
		return ImGuiKey_K;
		break;

	case KEY_L:
		return ImGuiKey_L;
		break;

	case KEY_M:
		return ImGuiKey_M;
		break;

	case KEY_N:
		return ImGuiKey_N;
		break;

	case KEY_O:
		return ImGuiKey_O;
		break;

	case KEY_P:
		return ImGuiKey_P;
		break;

	case KEY_Q:
		return ImGuiKey_Q;
		break;

	case KEY_R:
		return ImGuiKey_R;
		break;

	case KEY_S:
		return ImGuiKey_S;
		break;

	case KEY_T:
		return ImGuiKey_T;
		break;

	case KEY_U:
		return ImGuiKey_U;
		break;

	case KEY_V:
		return ImGuiKey_V;
		break;

	case KEY_W:
		return ImGuiKey_W;
		break;

	case KEY_X:
		return ImGuiKey_X;
		break;

	case KEY_Y:
		return ImGuiKey_Y;
		break;

	case KEY_Z:
		return ImGuiKey_Z;
		break;

	case KEY_F1:
		return ImGuiKey_F1;
		break;

	case KEY_F2:
		return ImGuiKey_F2;
		break;

	case KEY_F3:
		return ImGuiKey_F3;
		break;

	case KEY_F4:
		return ImGuiKey_F4;
		break;

	case KEY_F5:
		return ImGuiKey_F5;
		break;

	case KEY_F6:
		return ImGuiKey_F6;
		break;

	case KEY_F7:
		return ImGuiKey_F7;
		break;

	case KEY_F8:
		return ImGuiKey_F8;
		break;

	case KEY_F9:
		return ImGuiKey_F9;
		break;

	case KEY_F10:
		return ImGuiKey_F10;
		break;

	case KEY_F11:
		return ImGuiKey_F11;
		break;

	case KEY_F12:
		return ImGuiKey_F12;
		break;

	case KEY_SHIFT:
		return ImGuiKey_LeftShift;
		break;

	case KEY_RSHIFT:
		return ImGuiKey_RightShift;
		break;

	case KEY_CONTROL:
		return ImGuiKey_LeftCtrl;
		break;

	case KEY_RCONTROL:
		return ImGuiKey_RightCtrl;
		break;

	case KEY_ALT:
		return ImGuiKey_LeftAlt;
		break;

	case KEY_TAB:
		return ImGuiKey_Tab;
		break;

	case KEY_ENTER:
		return ImGuiKey_Enter;
		break;

	case KEY_BACKSPACE:
		return ImGuiKey_Backspace;
		break;

	case KEY_MLCLICK:
		return ImGuiKey_MouseLeft;
		break;

	case KEY_MRCLICK:
		return ImGuiKey_MouseRight;
		break;

	case KEY_MMIDDLEBUTTON:
		return ImGuiKey_MouseMiddle;
		break;

	case KEY_PLUS:  //es el +
		return ImGuiKey_Equal;
		break;

	case KEY_MINUS:
		return ImGuiKey_Minus;
		break;

	case KEY_PERIOD:
		return ImGuiKey_Period;
		break;

	case KEY_COMMA:
		return ImGuiKey_Comma;
		break;
	case NONE:
		return ImGuiKey_None;
		break;

	
	}
}
