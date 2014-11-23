#include <iostream>
#include "Game.h"
#include "ExampleStateA.h"

int main()
{
	Game game;

	sf::Font font;
    if (!font.loadFromFile("fonts/Montserrat-Regular.ttf"))
    {
        return -1;
    }

	game.pushState(new ExampleStateA(game, font));

	game.loop();

	return 0;
}
