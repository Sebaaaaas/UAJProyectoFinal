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

int ConversorInput(ImGuiKey key) {

	switch (key) {
	case ImGuiKey_Space:
		return 0x20;
		break;

	case ImGuiKey_LeftArrow:
		return 0x25;
		break;

	case ImGuiKey_UpArrow:
		return 0x26;
		break;

	case ImGuiKey_RightArrow:
		return 0x27;
		break;

	case ImGuiKey_DownArrow:
		return 0x28;
		break;

	case ImGuiKey_0:
		return 0x30;
		break;

	case ImGuiKey_1:
		return 0x31;
		break;

	case ImGuiKey_2:
		return 0x32;
		break;

	case ImGuiKey_3:
		return 0x33;
		break;

	case ImGuiKey_4:
		return 0x34;
		break;

	case ImGuiKey_5:
		return 0x35;
		break;

	case ImGuiKey_6:
		return 0x36;
		break;

	case ImGuiKey_7:
		return 0x37;
		break;

	case ImGuiKey_8:
		return 0x38;
		break;

	case ImGuiKey_9:
		return 0x39;
		break;

	case ImGuiKey_A:
		return 0x41;
		break;

	case ImGuiKey_B:
		return 0x42;
		break;

	case ImGuiKey_C:
		return 0x43;
		break;

	case ImGuiKey_D:
		return 0x44;
		break;

	case ImGuiKey_E:
		return 0x45;
		break;

	case ImGuiKey_F:
		return 0x46;
		break;

	case ImGuiKey_G:
		return 0x47;
		break;

	case ImGuiKey_H:
		return 0x48;
		break;

	case ImGuiKey_I:
		return 0x49;
		break;

	case ImGuiKey_J:
		return 0x4A;
		break;

	case ImGuiKey_K:
		return 0x4B;
		break;

	case ImGuiKey_L:
		return 0x4C;
		break;

	case ImGuiKey_M:
		return 0x4D;
		break;

	case ImGuiKey_N:
		return 0x4E;
		break;

	case ImGuiKey_O:
		return 0x4F;
		break;

	case ImGuiKey_P:
		return 0x50;
		break;

	case ImGuiKey_Q:
		return 0x51;
		break;

	case ImGuiKey_R:
		return 0x52;
		break;

	case ImGuiKey_S:
		return 0x53;
		break;

	case ImGuiKey_T:
		return 0x54;
		break;

	case ImGuiKey_U:
		return 0x55;
		break;

	case ImGuiKey_V:
		return 0x56;
		break;

	case ImGuiKey_W:
		return 0x57;
		break;

	case ImGuiKey_X:
		return 0x58;
		break;

	case ImGuiKey_Y:
		return 0x59;
		break;

	case ImGuiKey_Z:
		return 0x5A;
		break;

	case ImGuiKey_F1:
		return 0x70;
		break;

	case ImGuiKey_F2:
		return 0x71;
		break;

	case ImGuiKey_F3:
		return 0x72;
		break;

	case ImGuiKey_F4:
		return 0x73;
		break;

	case ImGuiKey_F5:
		return 0x74;
		break;

	case ImGuiKey_F6:
		return 0x75;
		break;

	case ImGuiKey_F7:
		return 0x76;
		break;

	case ImGuiKey_F8:
		return 0x77;
		break;

	case ImGuiKey_F9:
		return 0x78;
		break;

	case ImGuiKey_F10:
		return 0x79;
		break;

	case ImGuiKey_F11:
		return 0x7A;
		break;

	case ImGuiKey_F12:
		return 0x7B;
		break;

	case ImGuiKey_F13:
		return 0x7C;
		break;

	case ImGuiKey_F14:
		return 0x7D;
		break;

	case ImGuiKey_F15:
		return 0x7E;
		break;

	case ImGuiKey_F16:
		return 0x7F;
		break;

	case ImGuiKey_F17:
		return 0x80;
		break;

	case ImGuiKey_F18:
		return 0x81;
		break;

	case ImGuiKey_F19:
		return 0x82;
		break;

	case ImGuiKey_F20:
		return 0x83;
		break;

	case ImGuiKey_F21:
		return 0x84;
		break;

	case ImGuiKey_F22:
		return 0x85;
		break;

	case ImGuiKey_F23:
		return 0x86;
		break;

	case ImGuiKey_F24:
		return 0x87;
		break;

	case ImGuiKey_LeftShift:
		return 0x10;
		break;

	case ImGuiKey_RightShift:
		return 0x10;
		break;

	case ImGuiKey_LeftCtrl:
		return 0x11;
		break;

	case ImGuiKey_RightCtrl:
		return 0x11;
		break;

	case ImGuiKey_LeftAlt:
		return 0x12;
		break;

	case ImGuiKey_Tab:
		return 0x09;
		break;

	case ImGuiKey_Enter:
		return 0x0D;
		break;

	case ImGuiKey_Backspace:
		return 0x08;
		break;

	case ImGuiKey_MouseLeft:
		return 1;
		break;

	case ImGuiKey_MouseRight:
		return 2;
		break;

	case ImGuiKey_MouseMiddle:
		return 3;
		break;

	case ImGuiKey_Equal:  //es el +
		return 0xBB;
		break;

	case ImGuiKey_Minus:
		return 0xBD;
		break;

	case ImGuiKey_Period:
		return 0xBE;
		break;

	case ImGuiKey_Comma:
		return 0xBC;
		break;

	default:
		return 0;
	}

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
		WS_OVERLAPPEDWINDOW, 
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

	std::string buttonLabel = "Click Me";
	bool waitForInput = false;

	std::string buttonLabelLT = "B: LT";
	bool waitForInputLT = false;

	std::string buttonLabelLB = "B: LB";
	bool waitForInputLB = false;

	std::string buttonLabelRT = "B: RT";
	bool waitForInputRT = false;

	std::string buttonLabelRB = "B: RB";
	bool waitForInputRB = false;

	std::string buttonLabelY = "B: Y";
	bool waitForInputY = false;

	std::string buttonLabelX = "B: X";
	bool waitForInputX = false;

	std::string buttonLabelA = "B: A";
	bool waitForInputA = false;

	std::string buttonLabelB = "B: B";
	bool waitForInputB= false;

	std::string buttonLabelLS = "LS";
	bool waitForInputLS = false;

	std::string buttonLabelRS = "RS";
	bool waitForInputRS = false;

	std::string buttonLabelU = "UP";
	bool waitForInputU = false;

	std::string buttonLabelD = "DOWN";
	bool waitForInputD = false;

	std::string buttonLabelL = "LEFT";
	bool waitForInputL = false;

	std::string buttonLabelR = "RIGHT";
	bool waitForInputR = false;

	std::string buttonLabelSTR = "START";
	bool waitForInputSTR = false;

	std::string buttonLabelSLC = "SELECT";
	bool waitForInputSLC = false;

	bool checkL = false;
	bool checkR = false;


	//Parte Mem.Compartida
	std::array<int, 16>t;
	int numElems = 16;
	LPCWSTR name = L"SharedMemory"; 
	const size_t size = numElems*sizeof(int);
	// Intentar abrir un archivo de memoria compartida existente
	HANDLE hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // Permisos de lectura y escritura
		FALSE,                 // Manejo no heredable
		name);                 // Nombre del archivo de memoria compartida
 
	if (hMapFile == NULL) {
		// Crear un archivo de memoria compartida
		hMapFile = CreateFileMappingW(
			INVALID_HANDLE_VALUE,    // Usa la memoria de paginación del sistema
			NULL,                    // Seguridad por defecto
			PAGE_READWRITE,          // Permisos de lectura y escritura
			0,                       // Tamaño máximo de archivo (parte alta de 32 bits)
			size,                    // Tamaño máximo de archivo (parte baja de 32 bits)
			name);                   // Nombre del archivo de memoria compartida

		if (hMapFile == NULL) {
			std::cerr << "Could not create file mapping object (" << GetLastError() << ").\n";
			return 1;
		}
	}
	
	// Mapear una vista del archivo de memoria compartida
	LPVOID pBuf = MapViewOfFile(
		hMapFile,                // Manejador del archivo de memoria compartida
		FILE_MAP_ALL_ACCESS,     // Permisos de lectura y escritura
		0,
		0,
		size);

	if (pBuf == NULL) {
		std::cerr << "Could not map view of file (" << GetLastError() << ").\n";
		CloseHandle(hMapFile);
		return 1;
	}


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

		//boton LT
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.1f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.15f); // Centrar verticalmente 
		
		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelLT.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputLT = true;
			detectedKey = ImGuiKey_None;
			buttonLabelLT = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputLT) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputLT = false;
					buttonLabelLT = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[0] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton LB
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.1f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.26f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelLB.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputLB = true;
			detectedKey = ImGuiKey_None;
			buttonLabelLB = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputLB) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputLB = false;
					buttonLabelLB = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[1] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton RT
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.89f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.15f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelRT.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputRT = true;
			detectedKey = ImGuiKey_None;
			buttonLabelRT = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputRT) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputRT = false;
					buttonLabelRT = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[2] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton RB
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.89f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.26f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelRB.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputRB = true;
			detectedKey = ImGuiKey_None;
			buttonLabelRB = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputRB) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputRB = false;
					buttonLabelRB = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[3] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton Y
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.88f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.42f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelY.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputY = true;
			detectedKey = ImGuiKey_None;
			buttonLabelY = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputY) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputY = false;
					buttonLabelY = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[4] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton X
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.88f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.50f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelX.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputX = true;
			detectedKey = ImGuiKey_None;
			buttonLabelX = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputX) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputX = false;
					buttonLabelX = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[5] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton A
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.88f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.58f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelA.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputA = true;
			detectedKey = ImGuiKey_None;
			buttonLabelA = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputA) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputA = false;
					buttonLabelA = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[6] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton B
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.88f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.66f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelB.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputB = true;
			detectedKey = ImGuiKey_None;
			buttonLabelB = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputB) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputB = false;
					buttonLabelB = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[7] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton RS
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.63f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.9f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelRS.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputRS = true;
			detectedKey = ImGuiKey_None;
			buttonLabelRS = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputRS) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputRS = false;
					buttonLabelRS = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[8] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton LS
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.39f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.9f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelLS.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputLS = true;
			detectedKey = ImGuiKey_None;
			buttonLabelLS = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputLS) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputLS = false;
					buttonLabelLS = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[9] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton UP
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.1f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.55f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelU.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputU = true;
			detectedKey = ImGuiKey_None;
			buttonLabelU = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputU) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputU = false;
					buttonLabelU = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[10] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton DOWN
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.1f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.65f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelD.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputD = true;
			detectedKey = ImGuiKey_None;
			buttonLabelD = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputD) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputD = false;
					buttonLabelD = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[11] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton LEFT
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.1f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.60f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelL.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputL = true;
			detectedKey = ImGuiKey_None;
			buttonLabelL = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputL) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputL = false;
					buttonLabelL = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[12] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton RIGHT
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.1f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.70f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelR.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputR = true;
			detectedKey = ImGuiKey_None;
			buttonLabelR = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputR) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputR = false;
					buttonLabelR = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[13] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//boton SELECT
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.4f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.1f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelSLC.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputSLC = true;
			detectedKey = ImGuiKey_None;
			buttonLabelSLC = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputSLC) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputSLC = false;
					buttonLabelSLC = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[14] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}
		//boton START
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth) * 0.58f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.1f); // Centrar verticalmente 

		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabelSTR.c_str()))) {
			// Activar la espera del siguiente input
			waitForInputSTR = true;
			detectedKey = ImGuiKey_None;
			buttonLabelSTR = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInputSTR) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInputSTR = false;
					buttonLabelSTR = std::string(ImGui::GetKeyName(detectedKey));
					int si = ConversorInput(key);
					t[15] = si;
					memcpy(pBuf, &t, size);
					break;
				}
			}
		}

		//checkbox de los joysticks
		 
		ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

		//Left CheckBox 
		ImGui::SetCursorPosX((windowWidth) * 0.35f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.9f); // Centrar verticalmente 

		if (ImGui::Checkbox("", &checkL)) {
			if (checkL) {
				// Código a ejecutar cuando la checkbox está marcada
			}
			else {
				// Código a ejecutar cuando la checkbox no está marcada
			}
		}
		
		//Right CheckBox
		ImGui::SetCursorPosX((windowWidth) * 0.58f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.9f); // Centrar verticalmente 

		if (ImGui::Checkbox("", &checkR)) {
			if (checkR) {
				// Código a ejecutar cuando la checkbox está marcada
			}
			else {
				// Código a ejecutar cuando la checkbox no está marcada
			}
		}

		//comentario de explicacion
		ImGui::SetCursorPosX((windowWidth) * 0.4f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight) * 0.95f); // Centrar verticalmente 
		ImGui::Text("click ckeckbox to capture mouse movement");

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

	}
	
	// Limpieza
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
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

	return 0;
}

