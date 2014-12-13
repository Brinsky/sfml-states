#include "ExampleStateA.h"

#include <memory>

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

void ExampleStateA::event(sf::Event a_event)
{
    if (a_event.type == sf::Event::KeyReleased)
    {
        if (a_event.key.code == sf::Keyboard::Space)
        {
            game.changeState(std::unique_ptr<GameState>(new ExampleStateB(game, font)));
        }
    }
}

void ExampleStateA::tick()
{

}

void ExampleStateA::draw(sf::RenderTarget& a_target, sf::RenderStates a_states)
{
    a_target.draw(shape, a_states);
    a_target.draw(text, a_states);
    a_target.draw(pressSpace, a_states);
}
