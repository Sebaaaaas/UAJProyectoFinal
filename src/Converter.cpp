#include "Converter.h"

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
