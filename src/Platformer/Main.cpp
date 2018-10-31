#include "Engine/Game.h"

#include "State_DebugMenu.h"
#include "State_Intro.h"
#include "State_Game.h"


int main(int argc, char* argv[])
{
	Kengine::Game<GameState> game;
	game.RegisterState<State_DebugMenu>(GameState::DEBUG_MENU);
	game.RegisterState<State_Intro>(GameState::TITLE);
	game.RegisterState<State_Game>(GameState::GAME);
	game.Init("Platform Game", 800, 600, GameState::DEBUG_MENU);

	while(game.IsRunning())
	{
		game.Update();
		game.Draw();
	}
	
	return EXIT_SUCCESS;
}
