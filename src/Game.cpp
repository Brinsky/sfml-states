#include "Game.h"
#include "GameState.h"

/// Initializes any game related data
Game::Game() : window(sf::VideoMode(200, 200), "SFML States")
{
	running = true;
}

/// Cleans up both game and state related data
Game::~Game()
{
	// Empty the stack of GameStates and properly destroy the GameStates
	while(!states.empty())
	{
		// In order to call state destructors, state pointers must be
		// explicitly deleted
		delete states.back();
		states.pop_back();
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
		states.back()->event(a_event);
	}
}

/// Performs actions for both the Game and it's current GameState
void Game::masterTick()
{
    tick();

	if(!states.empty())
	{
		states.back()->tick();
	}
}

/// Draws both the Game and it's current GameState
void Game::masterDraw()
{
	window.clear();

	draw();

	if(!states.empty())
	{
		states.back()->draw(window, sf::RenderStates::Default);
	}

	window.display();
}

//~--- State stack management functions

/// Pop the current GameState and push a new one
void Game::changeState(GameState* a_state)
{
	if(!states.empty())
	{
		// The explicit deletion is necessary, see destructor
		delete states.back();
		states.pop_back();
	}

	pushState(a_state);

	// GameStates start paused
	a_state->resume();
}

/// Push a GameState onto the stack
void Game::pushState(GameState* a_state)
{
	if(!states.empty())
	{
		states.back()->pause();
	}

	states.push_back(a_state);

	// GameStates start paused
	a_state->resume();
}

/// Pop a GameState off of the stack
void Game::popState()
{
	if(!states.empty())
	{
		// The explicit deletion is necessary, see destructor
		delete states.back();
		states.pop_back();

		// Resume previous state
		states.back()->resume();
	}
}

//~--- Lifetime functions

/// Signals intention to exit the game at the next opportunity
void Game::quit()
{
	running = false;
}
