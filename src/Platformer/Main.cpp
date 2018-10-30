#include "Engine/Game.h"

#include "DebugMenu_State.h"
#include "State_Intro.h"


int main(int argc, char* argv[])
{
	Kengine::Game<GameState> game;
	game.RegisterState<DebugMenu_State>(GameState::DEBUG_MENU);
	game.RegisterState<State_Intro>(GameState::TITLE);
	game.Init("Platform Game", 800, 600, GameState::DEBUG_MENU);

	while(game.IsRunning())
	{
		game.Update();
		game.Draw();
	}
	
	return EXIT_SUCCESS;
}
