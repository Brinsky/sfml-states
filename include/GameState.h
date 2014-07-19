#ifndef GAME_STATE
#define GAME_STATE

#include <SFML/Graphics.hpp>
#include "Game.h"

/// A GameState represents a possible state of a Game
/// GameState is an abstract interface and must be subclassed
/// The structure of GameState is largely inspired by this post:
/// http://gamedevgeek.com/tutorials/managing-game-states-in-c/
class GameState
{
public:
	// No need for 'init' and 'cleanup' functions, we have constructors
	// and destructors to do that (and mandate it)
	GameState();
	// Destructor must be virtual to ensure proper destruction of
	// subclasses
	virtual ~GameState();

	// Pure virtual functions, must be implemented by subclass

	// Lifetime management functions
	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvent(sf::Event a_event) = 0;
	virtual void tick() = 0;
	virtual void draw() = 0;

protected:
	// No reason to be public, external state changes should be made with
	// game.changeState(state)
	void changeState(Game& a_game, GameState& a_state)
	{
		a_game.changeState(a_state);
	}
};

#endif
