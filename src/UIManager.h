#pragma once
#include <Windows.h>
#include <dwmapi.h>
#include <d3d11.h>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <wrl/client.h>
#include <wincodec.h>
#include <vector>

class Button;
class CheckBox;
class Slots;
class InputMapper;
class InputSimulator;
class Converter;
class UIManager {
private:
	UIManager();
	~UIManager();
	static UIManager* instance;
	bool initImGui(HINSTANCE hInstance, INT cmd_show);
	void closeImGui();
	bool loadTextureFromFile(const wchar_t* filename, ID3D11Device* device, ID3D11DeviceContext* device_context, ID3D11ShaderResourceView** texture);
	void initButtons(int windowWidth, int windowHeight, std::vector<Button*>& buttons, std::vector<CheckBox*>& joycheckboxes, std::vector<Slots*>& saveSlots);
	void renderButtons(int windowWidth, int windowHeight, std::vector<Button*>& buttons, std::vector<CheckBox*>& joycheckboxes,
		std::vector<Slots*>& saveSlots, bool& checkL, bool& checkR);

	int windowWidth;
	int windowHeight;
	HWND window;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> myTexture;
	WNDCLASSEXW wc;
	ID3D11Device* device;
	ID3D11DeviceContext* device_context;
	ID3D11RenderTargetView* render_target_view;
	IDXGISwapChain* swap_chain;
	std::vector<Button*> buttons;
	std::vector<CheckBox*> joycheckboxes;
	std::vector<Slots*> saveSlots;
	InputMapper* mapper; 
	InputSimulator* simulator; 
	Converter* conv;
	bool shutdown = false;
	bool checkL = false, checkR = false;
public:
	static bool Init(HINSTANCE hInstance, INT cmd_show);
	static void Release();
	static UIManager* GetInstance();
	void update();
	bool getShutdown();
	void shutdownManager();
	void setTools(InputMapper* mapper, InputSimulator* simulator);
	void setInitialConfiguration();
};