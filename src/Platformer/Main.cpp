#include "Engine/Window.h"
#include "Engine/StateManager.h"
#include "DebugMenu_State.h"

#include <iostream>

int main(int argc, char* argv[])
{
	Kengine::Window window("Platform Game", 640, 480);

	Kengine::StateManager stateManager(&window);
	stateManager.RegisterState<DebugMenu_State>(1);
	stateManager.SwitchTo(2);

	while(window.IsOpen())
	{
		window.GetRenderWindow()->clear(sf::Color(64, 0, 64, 255));

		window.HandleEvents();

		stateManager.Draw();

		window.GetRenderWindow()->display();
	}

	return EXIT_SUCCESS;
}
