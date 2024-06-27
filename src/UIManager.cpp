#include "UIManager.h"
#include <assert.h>
#include <iostream>
#include "InputMapper.h"
#include "InputSimulator.h"
#include "Converter.h"
#include "Button.h"
#include "CheckBox.h"
#include "Slots.h"
#include "DefInput.h"

UIManager* UIManager::instance = nullptr;

UIManager::UIManager()
{
	mapper = nullptr;
	simulator = nullptr;
	conv = nullptr;
	windowHeight = 0;
	windowWidth = 0;
	window = nullptr;
	wc = {};
	device = nullptr;
	device_context = nullptr;
	render_target_view = nullptr;
	swap_chain = nullptr;
}

UIManager::~UIManager()
{
	for (auto e : buttons) {
		delete e;
		e = nullptr;
	}
	for (auto e : joycheckboxes) {
		delete e;
		e = nullptr;
	}
	for (auto e : saveSlots) {
		delete e;
		e = nullptr;
	}
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	if (message == WM_CLOSE) {
		PostQuitMessage(0);
		UIManager::GetInstance()->shutdownManager();
		return 0L;
	}
	ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param);


	return DefWindowProc(window, message, w_param, l_param);
}

bool UIManager::initImGui(HINSTANCE hInstance, INT cmd_show)
{
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"Control emulator";

	RegisterClassExW(&wc);

	window = CreateWindowExW(
		0, //cómo es el formato de la ventana que vamos a crear(encima de todo...)
		wc.lpszClassName,
		L"Control emulator",
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);


	SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA); //queremos poder ver contenidos de ventana

	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.RefreshRate.Numerator = 60U;
	sd.BufferDesc.RefreshRate.Denominator = 1U;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1U;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2U;
	sd.OutputWindow = window;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	constexpr D3D_FEATURE_LEVEL levels[2]{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};

	D3D_FEATURE_LEVEL level{};

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0U,
		levels,
		2U,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		&level,
		&device_context
	);

	ID3D11Texture2D* back_buffer{ nullptr };
	swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));

	if (back_buffer) {
		device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
		back_buffer->Release();
	}
	else return false;

	ShowWindow(window, cmd_show);
	UpdateWindow(window);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, device_context);

	if (!loadTextureFromFile(L"Assets/image.png", device, device_context, &myTexture)) {
		MessageBox(NULL, L"Failed to load texture", L"Error", MB_OK);
		return false;
	}

	RECT windowRect;
	GetClientRect(window, &windowRect);
	windowWidth = windowRect.right - windowRect.left;
	windowHeight = windowRect.bottom - windowRect.top;

	initButtons();

	return true;
}

void UIManager::closeImGui()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();

	if (swap_chain)
		swap_chain->Release();

	if (device_context)
		device_context->Release();

	if (device)
		device->Release();

	if (render_target_view)
		render_target_view->Release();

	DestroyWindow(window);
	UnregisterClassW(wc.lpszClassName, wc.hInstance);
}

bool UIManager::loadTextureFromFile(const wchar_t* filename, ID3D11Device* device, ID3D11DeviceContext* device_context, ID3D11ShaderResourceView** texture)
{
	Microsoft::WRL::ComPtr<IWICImagingFactory> wicFactory;
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));
	if (FAILED(hr)) {
		return false;
	}

	Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
	hr = wicFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
	if (FAILED(hr)) {
		return false;
	}

	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
	hr = decoder->GetFrame(0, &frame);
	if (FAILED(hr)) {
		return false;
	}

	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
	hr = wicFactory->CreateFormatConverter(&converter);
	if (FAILED(hr)) {
		return false;
	}

	hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) {
		return false;
	}

	UINT width, height;
	frame->GetSize(&width, &height);

	std::vector<BYTE> imageData(width * height * 4);
	hr = converter->CopyPixels(nullptr, width * 4, static_cast<UINT>(imageData.size()), imageData.data());
	if (FAILED(hr)) {
		return false;
	}

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = imageData.data();
	subResource.SysMemPitch = width * 4;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	hr = device->CreateTexture2D(&desc, &subResource, &texture2D);
	if (FAILED(hr)) {
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;

	hr = device->CreateShaderResourceView(texture2D.Get(), &srvDesc, texture);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

void UIManager::initButtons()
{
	buttons.push_back(new Button("B: A", (windowWidth) * 0.88f, (windowHeight) * 0.58f, ButtonA)); //A
	buttons.push_back(new Button("B: B", (windowWidth) * 0.88f, (windowHeight) * 0.66f, ButtonB)); //B
	buttons.push_back(new Button("B: X", (windowWidth) * 0.88f, (windowHeight) * 0.50f, ButtonX)); //X
	buttons.push_back(new Button("B: Y", (windowWidth) * 0.88f, (windowHeight) * 0.42f, ButtonY)); //Y
	buttons.push_back(new Button("B: UP", (windowWidth) * 0.1f, (windowHeight) * 0.55f, DpadUp)); //UP
	buttons.push_back(new Button("B: DOWN", (windowWidth) * 0.1f, (windowHeight) * 0.65f, DpadDown)); //DOWN
	buttons.push_back(new Button("B: RIGHT", (windowWidth) * 0.1f, (windowHeight) * 0.70f, DpadRight)); //RIGHT
	buttons.push_back(new Button("B: LEFT", (windowWidth) * 0.1f, (windowHeight) * 0.60f, DpadLeft)); //LEFT
	buttons.push_back(new Button("B: LSL", (windowWidth) * 0.305f, (windowHeight) * 0.82f, LeftJoystickLeft)); //Left direction left joystick
	buttons.push_back(new Button("B: LSR", (windowWidth) * 0.38f, (windowHeight) * 0.82f, LeftJoystickRight)); //Right direction left joystick
	buttons.push_back(new Button("B: LSU", (windowWidth) * 0.345f, (windowHeight) * 0.77f, LeftJoystickUp)); //Up direction left joystick
	buttons.push_back(new Button("B: LSD", (windowWidth) * 0.345f, (windowHeight) * 0.88f, LeftJoystickDown)); //Down direction left joystick
	buttons.push_back(new Button("B: RSL", (windowWidth) * 0.537f, (windowHeight) * 0.82f, RightJoystickLeft)); //Left direction right joystick
	buttons.push_back(new Button("B: RSR", (windowWidth) * 0.615f, (windowHeight) * 0.82f, RightJoystickRight)); //Right direction right joystick
	buttons.push_back(new Button("B: RSU", (windowWidth) * 0.577f, (windowHeight) * 0.77f, RightJoystickUp)); //Up direction right joystick
	buttons.push_back(new Button("B: RSD", (windowWidth) * 0.577f, (windowHeight) * 0.88f, RightJoystickDown)); //Down direction right joystick
	buttons.push_back(new Button("B: LS", (windowWidth) * 0.42f, (windowHeight) * 0.88f, LeftJoystickButton)); //Left joystick button
	buttons.push_back(new Button("B: RS", (windowWidth) * 0.66f, (windowHeight) * 0.88f, RightJoystickButton)); //Right joystick button
	buttons.push_back(new Button("B: LB", (windowWidth) * 0.1f, (windowHeight) * 0.26f, LB)); //LB
	buttons.push_back(new Button("B: RB", (windowWidth) * 0.89f, (windowHeight) * 0.26f, RB)); //RB
	buttons.push_back(new Button("B: LT", (windowWidth) * 0.1f, (windowHeight) * 0.15f, LT)); //LT
	buttons.push_back(new Button("B: RT", (windowWidth) * 0.89f, (windowHeight) * 0.15f, RT)); //RT
	buttons.push_back(new Button("B: SELECT", (windowWidth) * 0.4f, (windowHeight) * 0.1f, ViewButton)); //Select
	buttons.push_back(new Button("B: START", (windowWidth) * 0.58f, (windowHeight) * 0.1f, MenuButton)); //Start

	//Botones de cargar y guardar
	buttons.push_back(new Button("SAVE", (windowWidth) * 0.05f, (windowHeight) * 0.9f, NotAKey)); //save
	buttons.push_back(new Button("LOAD", (windowWidth) * 0.15f, (windowHeight) * 0.9f, NotAKey)); //load

	//checkBoxs
	joycheckboxes.push_back(new CheckBox((windowWidth) * 0.23f, (windowHeight) * 0.88f, "LeftCheckbox")); //checkbox izquierdo
	joycheckboxes.push_back(new CheckBox((windowWidth) * 0.46f, (windowHeight) * 0.88f, "RightCheckbox")); //checkbox derecho

	//saveSlots
	saveSlots.push_back(new Slots("Slot 1", "controles.txt"));
	saveSlots.push_back(new Slots("Slot 2", "controles2.txt"));
	saveSlots.push_back(new Slots("Slot 3", "controles3.txt"));
}

void UIManager::renderButtons()
{
	if (mapper == nullptr || simulator == nullptr || conv == nullptr) {
		shutdown = true;
		std::cerr << "No se ha llamado al metodo setTools de UIManager" << std::endl;
		return;
	}

	ImGuiKey detectedKey = ImGuiKey_None;
	// Color de los botones
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

	for (int i = 0; i < buttons.size(); i++) {
		// Posicion del boton
		ImGui::SetCursorPosX(buttons[i]->getX()); // Centrar horizontalmente
		ImGui::SetCursorPosY(buttons[i]->getY()); // Centrar verticalmente 

		if (ImGui::Button(buttons[i]->getName().c_str())) {
			if (buttons[i]->getName() != "SAVE" && buttons[i]->getName() != "LOAD") {
				// Activar la espera del siguiente input
				buttons[i]->setWaiting(true);
				detectedKey = ImGuiKey_None;
				buttons[i]->setName("Press any key...");
				buttons[i]->setBackupName(buttons[i]->getName());
			}
			else if (buttons[i]->getName() == "SAVE") {
				ImGui::OpenPopup("SavePop");
			}
			else {
				
				ImGui::OpenPopup("LoadPop");
			}
		}

		// Mostrar el texto y detectar el siguiente input si esta esperando
		if (buttons[i]->getWaiting()) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					buttons[i]->setWaiting(false);
					buttons[i]->setName(std::string(ImGui::GetKeyName(detectedKey)));
					mapper->setButton(buttons[i]->getKey(), conv->convertInput(key));
					buttons[i]->setBackupName(buttons[i]->getName());
				}
			}
		}

		//si un boton del mando esta siendo pulsado se podra ver cual es en la UI
		if (i < simulator->numButtons) {
			if (simulator->getPressed(i)) {
				buttons[i]->setName("Pressed");
			}
			else if (buttons[i]->getName() != buttons[i]->getBackupName() && buttons[i]->getName() != buttons[i]->getInitialName()) {
				buttons[i]->setName(buttons[i]->getBackupName());
			}
		}
	}

	//checkbox de los joysticks

	ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

	for (int c = 0; c < joycheckboxes.size(); c++) {
		ImGui::SetCursorPosX(joycheckboxes[c]->getX()); // Centrar horizontalmente
		ImGui::SetCursorPosY(joycheckboxes[c]->getY()); // Centrar verticalmente 

		ImGui::Text(joycheckboxes[c]->getName().c_str());
		ImGui::SameLine();
		//Dado que vamos a tener controles izquierdo y derecho debemos comprobar si cualquiera de los 2 esta activo
		if (c == 0) {
			if (ImGui::Checkbox("##LeftCheckbox", &checkL)) {

				simulator->setLeftMovement(checkL);

			}
		}
		if (c == 1) {

			if (ImGui::Checkbox("##RightCheckbox", &checkR)) {

				simulator->setRightMovement(checkR);

			}
		}

	}

	ImGui::SetCursorPosX((windowWidth) * 0.3f); // Centrar horizontalmente
	ImGui::SetCursorPosY((windowHeight) * 0.95f); // Centrar verticalmente 
	ImGui::Text("Click one ckeckbox to capture mouse movement with joystick");
}

void UIManager::shutdownManager()
{
	shutdown = true;
}

void UIManager::update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	RECT windowRect;
	GetClientRect(window, &windowRect);

	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
	ImGui::SetNextWindowSize(ImVec2(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top));

	//panel de botones
	if (!ImGui::Begin("Controls", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
		ImGui::End();
		shutdown = true;
		return;
	}

	//imagen del mando
	ImGui::GetBackgroundDrawList()->AddImage((void*)myTexture.Get(), ImVec2(0, 0), ImVec2(windowWidth, windowHeight));

	//Render de los botones y las checkboxes
	renderButtons();

	//popup para guardar el preset
	if (ImGui::BeginPopup("SavePop"))
	{
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Choose which slot you want to save");
		bool selected = false;
		int k = 0;
		while (!selected && k < saveSlots.size()) {
			if (ImGui::Button(saveSlots[k]->getName().c_str())) {
				mapper->saveControls(checkL, checkR, saveSlots[k]->getFile().c_str());
				ImGui::CloseCurrentPopup();
				selected = true;
			}
			k++;
		}
		ImGui::EndPopup();
	}

	//popup para cargar el preset
	if (ImGui::BeginPopup("LoadPop")) {
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "What preset do you want to load?");
		bool isbuttonpressed = false;
		int l = 0;
		while (!isbuttonpressed && l < saveSlots.size()) {
			if (ImGui::Button(saveSlots[l]->getName().c_str())) {
				mapper->loadControls(checkL, checkR, saveSlots[l]->getFile().c_str());
				isbuttonpressed = true;
			}
			l++;
		}

		// Se utiliza el booleano para que se actualizen en la ui los controles al cargar el preset
		if (isbuttonpressed) {
			simulator->setRightMovement(checkR);
			simulator->setLeftMovement(checkL);
			std::vector<std::pair<KeyboardKey, ControllerLayout>>* b = mapper->getButtons();
			for (int i = 0; i < b->size(); i++)
			{
				if ((*b)[i].first != NONE) {
					buttons[i]->setName(std::string(ImGui::GetKeyName(conv->convertToImGUiKey((*b)[i].first))));
					buttons[i]->setBackupName(buttons[i]->getName());
				}
				else {
					buttons[i]->setName(std::string(buttons[i]->getInitialName()));
					buttons[i]->setBackupName(buttons[i]->getName());
				}

			}
			ImGui::CloseCurrentPopup();

		}

		ImGui::EndPopup();
	}

	ImVec2 windowSize = ImGui::GetWindowSize(); //windowSize.x *= 2; windowSize.y *= 2;

	ImGui::PopStyleColor(7); //esto es para quitar los push que se han hecho con PushStyleColor

	ImGui::End();

	//renderizado

	ImGui::Render();

	constexpr float color[4]{ 0.f,0.f ,0.f ,0.f };
	device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
	device_context->ClearRenderTargetView(render_target_view, color);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	swap_chain->Present(1U, 0U);
}

bool UIManager::getShutdown()
{
	return shutdown;
}

void UIManager::setTools(InputMapper* mapper, InputSimulator* simulator)
{
	this->mapper = mapper;
	this->simulator = simulator;
}

void UIManager::setInitialConfiguration()
{
	mapper->loadControls(checkL, checkR, saveSlots[0]->getFile().c_str());
	simulator->setRightMovement(checkR);
	simulator->setLeftMovement(checkL);
	std::vector<std::pair<KeyboardKey, ControllerLayout>>* b = mapper->getButtons();
	for (int i = 0; i < b->size(); i++)
	{
		if ((*b)[i].first != NONE) {
			buttons[i]->setName(std::string(ImGui::GetKeyName(conv->convertToImGUiKey((*b)[i].first))));
			buttons[i]->setBackupName(buttons[i]->getName());
		}
		else {
			buttons[i]->setName(std::string(buttons[i]->getInitialName()));
			buttons[i]->setBackupName(buttons[i]->getName());
		}

	}
}

bool UIManager::Init(HINSTANCE hInstance, INT cmd_show)
{
	assert(instance == nullptr);
	instance = new UIManager();

	instance->conv = new Converter();

	instance->initImGui(hInstance, cmd_show);

	return true;
}

void UIManager::Release()
{
	assert(instance != nullptr);

	instance->closeImGui();

	instance->mapper = nullptr;
	instance->simulator = nullptr;
	delete instance->conv;
	instance->conv = nullptr;

	delete instance;
	instance = nullptr;
}

UIManager* UIManager::GetInstance()
{
	assert(instance != nullptr);
	return instance;
}
