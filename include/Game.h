#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

// Forward declaration required to prevent circular dependency.
class GameState;

/// A Game manages an SFML window, SFML events, and GameStates.
/// The structure of Game was partly inspired by this post:
/// http://gamedevgeek.com/tutorials/managing-game-states-in-c/
class Game
{
public:
	Game();
	virtual ~Game();

	// Main loop functions
	void loop();

	// State management functions
    // Warning: These functions WILL delete the given states; the states must
    // be allocated dynamically (e.g. new State) before being passed.
	void changeState(std::unique_ptr<GameState> state);
	void pushState(std::unique_ptr<GameState> state);
	void popState();

	void quit();

protected:
    // Game loop functions, called in this order
    virtual void event(sf::Event a_event);
    virtual void tick();
	virtual void draw();

	sf::RenderWindow window;

private:
    // Proxy functions to ensure that both game loop and state loop functions
    // are called
    void masterEvent(sf::Event a_event);
	void masterTick();
	void masterDraw();

	std::vector<std::unique_ptr<GameState>> states;
	bool running;
};

#endif
