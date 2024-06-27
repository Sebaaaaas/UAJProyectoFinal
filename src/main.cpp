#include <iostream>
#include "InputMapper.h"
#include "InputSimulator.h"
#include "UIManager.h"

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show) {
	
	if (!UIManager::Init(instance, cmd_show)) {
		std::cerr << "Error al inicializar UIManager" << std::endl;
		return 1;
	}

	// Creacion de simulador y mapeador
	InputMapper* mapper = new InputMapper();
	InputSimulator* simulator = new InputSimulator();
	simulator->setMapper(mapper);

	UIManager::GetInstance()->setTools(mapper, simulator);

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
		
		UIManager::GetInstance()->update();
		running = !UIManager::GetInstance()->getShutdown();

		// Llamamos al update del simulador para que simule las teclas que sean necesarias
		simulator->update();

		Sleep(20);
	}
	
	delete simulator;
	simulator = nullptr;

	delete mapper;
	mapper = nullptr;

	UIManager::GetInstance()->Release();

	return 0;
}
