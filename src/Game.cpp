#include "Game.h"

#include <iostream>

#include "GameState.h"

/// Initializes any game related data
Game::Game(sf::RenderWindow& a_window) : window(a_window)
{
    running = true;
}

/// Cleans up both game and state related data
Game::~Game()
{
    // Empty the stack of GameStates and properly destroy the GameStates
    while(!states.empty())
    {
        states.pop();
    }

    window.close();
}

/// Loops all major game functions while the game is running
void Game::loop()
{
    sf::Event event;

    while (running)
    {
        while (window.pollEvent(event))
        {
            masterEvent(event);
        }

        masterTick();
        masterDraw();
    }
}

//~--- Game specific loop functions (should not call state loop functions!)

/// Responds to any Game-level SFML events
void Game::event(sf::Event a_event)
{
    // Handle window exit. Derived classes can call quit().
    if (a_event.type == sf::Event::Closed)
    {
        running = false;
    }

    // Override if more actions are desired
}

/// Performs any SFML-event-independent actions
void Game::tick()
{
    // Do nothing by default, override if desired
}

/// Performs any Game-level drawing
void Game::draw()
{
    // Do nothing by default, override if desired
}

//~--- Proxy loop functions

/// Handles events for both the Game and it's current GameState
void Game::masterEvent(sf::Event a_event)
{
    event(a_event);

    if(!states.empty())
    {
        states.top()->event(a_event);
    }
}

/// Performs actions for both the Game and it's current GameState
void Game::masterTick()
{
    tick();

    if(!states.empty())
    {
        states.top()->tick();
    }
}

/// Draws both the Game and it's current GameState
void Game::masterDraw()
{
    window.clear();

    draw();

    if(!states.empty())
    {
        states.top()->draw(window, sf::RenderStates::Default);
    }

    window.display();
}

//~--- State stack management functions

/// Pop the current GameState and push a new one
void Game::changeState(std::unique_ptr<GameState> state)
{
    if(!states.empty())
    {
        states.pop();
    }

    pushState(std::move(state));
}

/// Push a GameState onto the stack
void Game::pushState(std::unique_ptr<GameState> state)
{
    if(!states.empty())
    {
        states.top()->pause();
    }

    // GameStates start paused and must be resumed
    state->resume();

    states.push(std::move(state));
}

/// Pop a GameState off of the stack
void Game::popState()
{
    if(!states.empty())
    {
        states.pop();

        // Resume previous state
        states.top()->resume();
    }
}

//~--- Lifetime functions

/// Signals intention to exit the game at the next opportunity
void Game::quit()
{
    running = false;
}
