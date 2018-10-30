#include "Engine/Window.h"
#include "Engine/StateManager.h"
#include "Engine/EventManager.h"

#include "DebugMenu_State.h"

int main(int argc, char* argv[])
{
	Kengine::EventManager<GameState> eventManager("Resources/keys.cfg");

	Kengine::Window<GameState> window(&eventManager);
	window.Init("Platform Game", 640, 480);

	Kengine::StateManager<GameState> stateManager(&eventManager, &window);
	stateManager.RegisterState<DebugMenu_State>(GameState::DEBUG_MENU);
	stateManager.SwitchTo(GameState::DEBUG_MENU);

	while(window.IsOpen())
	{
		window.GetRenderWindow()->clear(sf::Color(64, 0, 64, 255));

		window.Update();

		stateManager.Draw();

		window.GetRenderWindow()->display();
	}

	return EXIT_SUCCESS;
}
