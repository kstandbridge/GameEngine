#include "Engine/Window.h"

int main(int argc, char* argv[])
{
	Kengine::Window window("Platform Game", 640, 480);
	while(window.IsOpen())
	{
		window.HandleEvents();
	}

	return EXIT_SUCCESS;
}
