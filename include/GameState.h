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
    GameState(Game& a_game);
    virtual ~GameState();

    // Lifetime management functions
    virtual void pause() = 0;
    virtual void resume() = 0;

    // State loop functions, called in this order
    virtual void event(sf::Event a_event) = 0;
    virtual void tick() = 0;
    virtual void draw(sf::RenderTarget& a_target,
        sf::RenderStates a_states) = 0;

protected:
    Game& game;
};

#endif
