#include "ExampleStateB.h"

#include <memory>
#include <iostream>

#include "ExampleStateA.h"

ExampleStateB::ExampleStateB(Game& a_game, sf::Font& a_font) :
    GameState(a_game),
    font(a_font),
    shape(100.f)
{
    shape.setFillColor(sf::Color::Red);

    text.setFont(font);
    text.setString("State B");
    text.setCharacterSize(25);
    text.setColor(sf::Color::Green);
    text.setPosition(75, 50);

    pressSpace.setFont(font);
    pressSpace.setString("(Press Space)");
    pressSpace.setCharacterSize(20);
    pressSpace.setColor(sf::Color::Green);
    pressSpace.setPosition(35, 120);
}

ExampleStateB::~ExampleStateB()
{

}

void ExampleStateB::pause()
{

}

void ExampleStateB::resume()
{

}

void ExampleStateB::event(sf::Time elapsed, sf::Event a_event)
{
    if (a_event.type == sf::Event::KeyPressed)
    {
        if (a_event.key.code == sf::Keyboard::Space)
        {
            std::cout << "Frame time: " << elapsed.asMilliseconds() << std::endl;

            game.changeState(
                std::unique_ptr<GameState>(new ExampleStateA(game, font)));
        }
    }
}

void ExampleStateB::update(sf::Time elapsed)
{

}

void ExampleStateB::draw(VirtualScreen& screen)
{
    screen.draw(shape);
    screen.draw(text);
    screen.draw(pressSpace);
}
