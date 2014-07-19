#include <iostream>
#include "ExampleGame.h"

int main()
{
	std::cout << "Howdy!" << std::endl;
	ExampleGame game;
	//StateA testState;

	//game.pushState(testState);
	
	sf::Event event;

	while (game.isRunning())
	{
		while (game.pollWindowEvent(event))
		{
			game.handleEvent(event);
		}

		game.tick();
		game.draw();
	}

	return 0;
}
