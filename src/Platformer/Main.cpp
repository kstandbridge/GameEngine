#include "Engine/Window.h"
#include "Engine/StateManager.h"
#include "Engine/EventManager.h"

#include "DebugMenu_State.h"
#include "State_Intro.h"

int main(int argc, char* argv[])
{
	Kengine::EventManager<GameState> eventManager("Resources/keys.cfg");

	Kengine::Window<GameState> window(&eventManager);
	window.Init("Platform Game", 800, 600);

	Kengine::StateManager<GameState> stateManager(&eventManager, &window);
	stateManager.RegisterState<DebugMenu_State>(GameState::DEBUG_MENU);
	stateManager.RegisterState<State_Intro>(GameState::TITLE);
	stateManager.SwitchTo(GameState::DEBUG_MENU);

	sf::Clock clock;
	sf::Time time;
	while(window.IsOpen())
	{
		window.GetRenderWindow()->clear(sf::Color(64, 0, 64, 255));

		window.Update();
		stateManager.Update(time);

		stateManager.Draw();

		window.GetRenderWindow()->display();

		time = clock.restart();
	}

	return EXIT_SUCCESS;
}
