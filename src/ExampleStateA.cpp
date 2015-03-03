#include "ExampleStateA.h"

#include <memory>
#include <iostream>

#include "ExampleStateB.h"

ExampleStateA::ExampleStateA(Game& a_game, sf::Font& a_font) :
    GameState(a_game),
    font(a_font),
    shape(100.f)
{
    shape.setFillColor(sf::Color::Green);

    text.setFont(font);
    text.setString("State A");
    text.setCharacterSize(25);
    text.setColor(sf::Color::Red);
    text.setPosition(75, 50);

    pressSpace.setFont(font);
    pressSpace.setString("(Press Space)");
    pressSpace.setCharacterSize(20);
    pressSpace.setColor(sf::Color::Red);
    pressSpace.setPosition(35, 120);
}

ExampleStateA::~ExampleStateA()
{

}

void ExampleStateA::pause()
{

}

void ExampleStateA::resume()
{

}

void ExampleStateA::event(sf::Time elapsed, sf::Event a_event)
{
    if (a_event.type == sf::Event::KeyPressed)
    {
        if (a_event.key.code == sf::Keyboard::Space)
        {
            std::cout << "Frame time: " << elapsed.asMilliseconds() << std::endl;

            game.changeState(
                std::unique_ptr<GameState>(new ExampleStateB(game, font)));
        }
    }
}

void ExampleStateA::update(sf::Time elapsed)
{

}

void ExampleStateA::draw(VirtualScreen& screen)
{
    screen.draw(shape);
    screen.draw(text);
    screen.draw(pressSpace);
}
