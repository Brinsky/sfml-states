#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.h"

/// A GameState represents a possible state of a Game.
/// GameState is an abstract interface and must be subclassed
/// The structure of GameState was largely inspired by this post:
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
        // Note: elapsed times are measured from the last frame, not as totals
        virtual void event(sf::Time elapsed, sf::Event a_event) = 0;
        virtual void update(sf::Time elapsed) = 0;
        virtual void draw(VirtualScreen& screen) = 0;

    protected:
        Game& game;
};

#endif
