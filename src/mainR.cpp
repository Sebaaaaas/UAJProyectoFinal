#include <Windows.h>
#include <dwmapi.h>
#include <d3d11.h>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void OnSize(HWND hwnd, UINT flag, int width, int height)
{
	// Handle resizing
	//m_wndEdit.SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	//SetWindowPos(hWnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
	if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param))
	/*if (message == WM_DESTROY) {
		return 0L;

		PostQuitMessage(0);
		return 0L;
	}*/

	switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0L;
		break;
		case WM_SIZE: {

			int width = LOWORD(l_param);  // Macro to get the low-order word.
			int height = HIWORD(l_param); // Macro to get the high-order word.

			// Respond to the message:
			OnSize(window, (UINT)w_param, width, height);

		}
			break;
		case WM_NCLBUTTONDOWN:
			PostQuitMessage(0);
			break;
		case WM_MOVE:
			SetWindowPos(window, 0, 0, 0, 516, 589, SWP_FRAMECHANGED | WS_VISIBLE);
			break;
			
		break;
	}

	return DefWindowProc(window, message, w_param, l_param);
}

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show) {
	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = instance;
	wc.lpszClassName = L"OVERLAY TEST";

	RegisterClassExW(&wc);

	const HWND window = CreateWindowExW(
		0, //cómo es el formato de la ventana que vamos a crear(encima de todo...)
		wc.lpszClassName,
		L"OVERLAY TEST",
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
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

		ImGui::GetBackgroundDrawList()->AddCircleFilled({ 500,500 }, 100.f, ImColor(1.f, 0.f,0.f));

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