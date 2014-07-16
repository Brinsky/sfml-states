#ifndef GAME
#define GAME

#include <vector>

// Forward declaration required to prevent circular dependency.
class GameState;

/// A Game manages GameStates.
/// Game is an abstract interface and must be subclassed.
/// The structure of Game is largely inspired by this post:
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

	// Non-virtual functions, subclasses can't change these

	// State management functions
	void changeState(GameState& a_state);
	void pushState(GameState& a_state);
	void popState(GameState& a_state);

	// Lifetime management functions
	bool isRunning();
	void quit();

	// Pure virtual functions, must be implemented by subclasses
	virtual void handleEvents() = 0;
	virtual void tick() = 0;
	virtual void draw() = 0;
	
private:
	std::vector<GameState*> states;
	bool running;
};

#endif
