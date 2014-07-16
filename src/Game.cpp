#include "Game.h"
#include "GameState.h"

/// 'Init' any game related data
Game::Game()
{
	running = true;
}

/// 'Cleanup' any game related data
Game::~Game()
{
	// Empty the stack of GameStates and properly destroy the GameStates
	while(!states.empty())
	{
		// Because states is a vector of pointers to GameStates, it
		// will not call GameState destructors when those pointers are
		// popped. It is critical to explicitly destroy the underlying
		// objects with 'delete'
		delete states.back();
		states.pop_back();	
	}
}

/// Pop the current GameState and push a new one
void Game::changeState(GameState& a_state)
{
	if(!states.empty())
	{
		// The explicit deletion is necessary, see destructor
		delete states.back();
		states.pop_back();	
	}

	pushState(a_state);

	// GameStates start paused
	a_state.resume();
}

/// Push a GameState onto the stack
void Game::pushState(GameState& a_state)
{
	if(!states.empty())
	{
		states.back()->pause();
	}

	states.push_back(&a_state);

	// GameStates start paused
	a_state.resume();
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

/// Presumably a master loop would use this as a cue to exit
bool Game::isRunning()
{
	return running;
}

void Game::quit()
{
	running = false;
}
