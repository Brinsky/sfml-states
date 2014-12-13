#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "ExampleStateA.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML States");

    Game game(window);

    sf::Font font;
    if (!font.loadFromFile("fonts/Montserrat-Regular.ttf"))
    {
        return -1;
    }

    game.pushState(std::unique_ptr<GameState>(new ExampleStateA(game, font)));

    game.loop();

    return 0;
}
