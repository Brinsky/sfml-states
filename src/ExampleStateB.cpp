#include "ExampleStateB.h"

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

void ExampleStateB::event(sf::Event a_event)
{
    if (a_event.type == sf::Event::KeyReleased)
    {
        if (a_event.key.code == sf::Keyboard::Space)
        {
           game.changeState(std::unique_ptr<ExampleStateA>(new ExampleStateA(game, font)));
        }
    }
}

void ExampleStateB::tick()
{

}

void ExampleStateB::draw(sf::RenderTarget& a_target, sf::RenderStates a_states)
{
    a_target.draw(shape, a_states);
    a_target.draw(text, a_states);
    a_target.draw(pressSpace, a_states);
}
