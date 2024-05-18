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
	wc.lpszClassName = L"OVERLAY TEST";

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> myTexture;

	RegisterClassExW(&wc);

	const HWND window = CreateWindowExW(
		0, //cómo es el formato de la ventana que vamos a crear(encima de todo...)
		wc.lpszClassName,
		L"OVERLAY TEST",
		WS_OVERLAPPEDWINDOW, 
		0, 0, 700, 420,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);
	
	SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA); //queremos poder ver contenidos de ventana

	{
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

	}

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

	bool waitForInput = false;
	ImGuiKey detectedKey = ImGuiKey_None;
	std::string buttonLabel = "Click Me";

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

		// Mostrar la imagen cargada
		RECT windowRect;
		GetClientRect(window, &windowRect);
		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		ImGui::Begin("Image Window", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

		//ImGui::TextColored(ImVec4(0, 0, 0, 1), "Testing text");
		ImGui::GetBackgroundDrawList()->AddImage((void*)myTexture.Get(), ImVec2(0, 0), ImVec2(windowWidth, windowHeight));
		static char str0[128] = "Hello, world!";
		ImGui::InputText("input text", str0, IM_ARRAYSIZE(str0));
		
		// Posicion del boton
		ImGui::SetCursorPosX((windowWidth - 100) * 0.5f); // Centrar horizontalmente
		ImGui::SetCursorPosY((windowHeight - 50) * 0.5f); // Centrar verticalmente

		// Color del boton
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		
		// boton input >>>>>>>>>>>>>>>>>
		if (ImGui::Button((buttonLabel.c_str()))) {
			// Activar la espera del siguiente input
			waitForInput = true;
			detectedKey = ImGuiKey_None;
			buttonLabel = "Press any key...";
		}

		// Mostrar el texto y detectar el siguiente input si est� esperando
		if (waitForInput) {
			// Detectar el input del teclado
			for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
				if (ImGui::IsKeyDown(key)) {
					detectedKey = key;
					waitForInput = false;
					buttonLabel = std::string(ImGui::GetKeyName(detectedKey));
					break;
				}
			}
		}
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>
		ImVec2 windowSize = ImGui::GetWindowSize(); //windowSize.x *= 2; windowSize.y *= 2;

		ImGui::PopStyleColor(2); //esto es para quitar los push que se han hecho con PushStyleColor

		ImGui::End();


		ImGui::ShowDemoWindow();

		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		//renderizado

		ImGui::Render();

		constexpr float color[4]{ 0.f,0.f ,0.f ,0.f };
		device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
		device_context->ClearRenderTargetView(render_target_view, color);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


		swap_chain->Present(1U, 0U);

	}

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

