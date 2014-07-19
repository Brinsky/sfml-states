#ifndef GAME
#define GAME

#include <vector>
#include <SFML/Graphics.hpp>

// Forward declaration required to prevent circular dependency.
class GameState;

/// A Game manages GameStates.
/// Game is (partially) an abstract interface and must be subclassed.
/// The structure of Game was partly inspired by this post:
/// http://gamedevgeek.com/tutorials/managing-game-states-in-c/
class Game
{
public:
	// No need for 'init' and 'cleanup' functions, we have constructors
	// and destructors to do that (and mandate it)
	Game();
	// Destructor must be virtual to ensure proper destruction of
	// subclasses
	virtual ~Game();

	void handleEvent(sf::Event a_event);
	void tick();
	void draw();

	// State management functions
	void changeState(GameState& a_state);
	void pushState(GameState& a_state);
	void popState();

	// Lifetime management functions
	bool isRunning();
	void quit();


protected:
	// Called by handleEvent()
	virtual void handleGameEvent(sf::Event a_event) = 0;

private:
	std::vector<GameState*> states;
	bool running;
};

#endif
