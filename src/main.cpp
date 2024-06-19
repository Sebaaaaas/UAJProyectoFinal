#include <Windows.h>
#include <dwmapi.h>
#include <d3d11.h>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <wrl/client.h>
#include <wincodec.h>
#include <vector>
#include <iostream>
#include <array>
#include "DefInput.h"
#include "InputMapper.h"
#include "InputSimulator.h"
#include "Converter.h"
#include "Button.h"
#include "CheckBox.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
	
	if (message == WM_CLOSE) {
		PostQuitMessage(0);
		return 0L;
	}
	if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param)) {

		/*if (message == WM_DESTROY) {
			return 0L;

			PostQuitMessage(0);
			return 0L;
		}*/

		//switch (message) {
		//	case WM_CLOSE: //si cerramos ventana salimos de la aplicacion
		//		PostQuitMessage(0);
		//		return 0L;
		//	break;
		//}

	}

	return DefWindowProc(window, message, w_param, l_param);
}

bool LoadTextureFromFile(const wchar_t* filename, ID3D11Device* device, ID3D11DeviceContext* device_context, ID3D11ShaderResourceView** texture) {
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



INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show) {
	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = instance;
	wc.lpszClassName = L"Control emulator";

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> myTexture;

	RegisterClassExW(&wc);

	const HWND window = CreateWindowExW(
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

	/*{
		RECT client_area{};
		GetClientRect(window, &client_area);

		RECT window_area{};
		GetClientRect(window, &window_area);

		POINT diff{};
		ClientToScreen(window, &diff);

		const MARGINS margins{
			window_area.left + (diff.x - window_area.left),
			window_area.top + (diff.y - window_area.top),
			client_area.right,
			client_area.bottom
		};

		DwmExtendFrameIntoClientArea(window, &margins);

	}*/

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

	ID3D11Device* device{ nullptr };
	ID3D11DeviceContext* device_context{ nullptr };
	IDXGISwapChain* swap_chain{ nullptr };
	ID3D11RenderTargetView* render_target_view{ nullptr };
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
	else {
		return 1;
	}

	ShowWindow(window, cmd_show);
	UpdateWindow(window);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, device_context);

	if (!LoadTextureFromFile(L"Assets/image.png", device, device_context, &myTexture)) {
		MessageBox(NULL, L"Failed to load texture", L"Error", MB_OK);
		return 1;
	}

	//declaración de variables de botones
	ImGuiKey detectedKey = ImGuiKey_None;


	RECT windowRect;
	GetClientRect(window, &windowRect);
	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;


	std::vector<Button*> buttons;
	buttons.push_back(new Button("B: LT", (windowWidth) * 0.1f, (windowHeight) * 0.15f, LT)); //LT
	buttons.push_back(new Button("B: LB", (windowWidth) * 0.1f, (windowHeight) * 0.26f, LB)); //LB
	buttons.push_back(new Button("B: RT", (windowWidth) * 0.89f, (windowHeight) * 0.15f, RT)); //RT
	buttons.push_back(new Button("B: RB", (windowWidth) * 0.89f, (windowHeight) * 0.26f, RB)); //RB
	buttons.push_back(new Button("B: Y", (windowWidth) * 0.88f, (windowHeight) * 0.42f, ButtonY)); //Y
	buttons.push_back(new Button("B: X", (windowWidth) * 0.88f, (windowHeight) * 0.50f, ButtonX)); //X
	buttons.push_back(new Button("B: A", (windowWidth) * 0.88f, (windowHeight) * 0.58f, ButtonA)); //A
	buttons.push_back(new Button("B: B", (windowWidth) * 0.88f, (windowHeight) * 0.66f, ButtonB)); //B
	buttons.push_back(new Button("B: LS", (windowWidth) * 0.42f, (windowHeight) * 0.88f, LeftJoystickButton)); //Left joystick button
	buttons.push_back(new Button("B: RS", (windowWidth) * 0.66f, (windowHeight) * 0.88f, RightJoystickButton)); //Right joystick button
	buttons.push_back(new Button("B: UP", (windowWidth) * 0.1f, (windowHeight) * 0.55f,DpadUp)); //UP
	buttons.push_back(new Button("B: DOWN", (windowWidth) * 0.1f, (windowHeight) * 0.65f, DpadDown)); //DOWN
	buttons.push_back(new Button("B: LEFT", (windowWidth) * 0.1f, (windowHeight) * 0.60f, DpadLeft)); //LEFT
	buttons.push_back(new Button("B: RIGHT", (windowWidth) * 0.1f, (windowHeight) * 0.70f, DpadRight)); //RIGHT
	buttons.push_back(new Button("B: START", (windowWidth) * 0.58f, (windowHeight) * 0.1f,MenuButton)); //Start
	buttons.push_back(new Button("B: SELECT", (windowWidth) * 0.4f, (windowHeight) * 0.1f,ViewButton)); //Select

	buttons.push_back(new Button("B: LSU", (windowWidth) * 0.345f, (windowHeight) * 0.77f, LeftJoystickUp)); //Up direction left joystick
	buttons.push_back(new Button("B: LSD", (windowWidth) * 0.345f, (windowHeight) * 0.88f, LeftJoystickDown)); //Down direction left joystick
	buttons.push_back(new Button("B: LSL", (windowWidth) * 0.305f, (windowHeight) * 0.82f, LeftJoystickLeft)); //Left direction left joystick
	buttons.push_back(new Button("B: LSR", (windowWidth) * 0.38f, (windowHeight) * 0.82f, LeftJoystickRight)); //Right direction left joystick

	buttons.push_back(new Button("B: RSU", (windowWidth) * 0.577f, (windowHeight) * 0.77f, RightJoystickUp)); //Up direction right joystick
	buttons.push_back(new Button("B: RSD", (windowWidth) * 0.577f, (windowHeight) * 0.88f, RightJoystickDown)); //Down direction right joystick
	buttons.push_back(new Button("B: RSL", (windowWidth) * 0.537f, (windowHeight) * 0.82f, RightJoystickLeft)); //Left direction right joystick
	buttons.push_back(new Button("B: RSR", (windowWidth) * 0.615f, (windowHeight) * 0.82f, RightJoystickRight)); //Right direction right joystick

	//Checkbox
	std::vector<CheckBox*> joycheckboxes;
	joycheckboxes.push_back(new CheckBox((windowWidth) * 0.23f, (windowHeight) * 0.88f)); //checkbox izquierdo
	joycheckboxes.push_back(new CheckBox((windowWidth) * 0.46f, (windowHeight) * 0.88f)); //checkbox derecho

	bool checkL = false;
	bool checkR = false;

	//Conversor
	Converter* conv = new Converter();

	// Creacion de simulador y mapeador
	InputMapper* mapper = new InputMapper();
	InputSimulator* simulator = new InputSimulator();
	simulator->setMapper(mapper);

	bool running = true;
	while (running) {
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg); //relacionado con input de teclado
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				running = false;
			}
		}

		if (!running) {
			break;
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		
		RECT windowRect;
		GetClientRect(window, &windowRect);
		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		//panel de botones
		if (!ImGui::Begin("Controls", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
			ImGui::End();
			return 1;
		}

		//imagen del mando
		ImGui::GetBackgroundDrawList()->AddImage((void*)myTexture.Get(), ImVec2(0, 0), ImVec2(windowWidth, windowHeight));		

		// Color de los botones
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

		for (int i = 0; i < buttons.size(); i++) {
			// Posicion del boton
			ImGui::SetCursorPosX(buttons[i]->GetX()); // Centrar horizontalmente
			ImGui::SetCursorPosY(buttons[i]->GetY()); // Centrar verticalmente 

			// boton input >>>>>>>>>>>>>>>>>
			if (ImGui::Button(buttons[i]->GetName().c_str())) {
				// Activar la espera del siguiente input
				buttons[i]->SetWaiting(true);
				detectedKey = ImGuiKey_None;
				buttons[i]->SetName("Press any key...");
			}

			// Mostrar el texto y detectar el siguiente input si est  esperando
			if (buttons[i]->GetWaiting()) {
				// Detectar el input del teclado
				for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
					if (ImGui::IsKeyDown(key)) {
						detectedKey = key;
						buttons[i]->SetWaiting(false);
						buttons[i]->SetName(std::string(ImGui::GetKeyName(detectedKey)));
						mapper->setButton(buttons[i]->GetKey(), conv->convertInput(key));
						break;
					}
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
			ImGui::SetCursorPosX(joycheckboxes[c]->GetX()); // Centrar horizontalmente
			ImGui::SetCursorPosY(joycheckboxes[c]->GetY()); // Centrar verticalmente 
			if (c == 0) {
				ImGui::Text("LeftCheckbox");
				ImGui::SameLine();

				if (ImGui::Checkbox("##LeftCheckbox", &checkL)) {

					simulator->setLeftMovement(checkL);

				}
			}
			if (c == 1) {
				ImGui::Text("RightCheckbox");
				ImGui::SameLine();


				if (ImGui::Checkbox("##RightCheckbox", &checkR)) {

					simulator->setRightMovement(checkR);

				}
			}

		}
		
		//comentario de explicacion
		ImGui::SetCursorPosX((windowWidth) * 0.3f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.95f); // Centrar verticalmente 
		ImGui::Text("click one ckeckbox to capture mouse movement with joystick");

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		ImVec2 windowSize = ImGui::GetWindowSize(); //windowSize.x *= 2; windowSize.y *= 2;

		ImGui::PopStyleColor(7); //esto es para quitar los push que se han hecho con PushStyleColor

		ImGui::End();


		//ImGui::ShowDemoWindow();

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		//renderizado

		ImGui::Render();

		constexpr float color[4]{ 0.f,0.f ,0.f ,0.f };
		device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
		device_context->ClearRenderTargetView(render_target_view, color);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		swap_chain->Present(1U, 0U);

		// Llamamos al update del simulador para que simule las teclas que sean necesarias
		simulator->update();

		Sleep(20);
	}
	
	// Limpieza
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

	delete simulator;
	simulator = nullptr;

	delete mapper;
	mapper = nullptr;

	return 0;
}