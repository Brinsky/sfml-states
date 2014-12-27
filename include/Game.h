#ifndef GAME_H
#define GAME_H

#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>

#include "CenteredSprite.h"

// Forward declaration, required to prevent circular dependency
class GameState;

/// A Game manages an SFML window, SFML events, and GameStates.
/// The structure of Game was partly inspired by this post:
/// http://gamedevgeek.com/tutorials/managing-game-states-in-c/
class Game
{
    public:
        Game(sf::RenderWindow& window, sf::RenderTexture& virtualScreen);
        virtual ~Game();

        // Main loop method
        void loop();

        // State management methods
        void changeState(std::unique_ptr<GameState> state);
        void pushState(std::unique_ptr<GameState> state);
        void popState();

        void quit();

    protected:
        sf::RenderWindow& window;
        sf::RenderTexture& virtualScreen;

    private:
        // Game loop methods, called in this order
        virtual void event(sf::Event a_event);
        virtual void tick();
        virtual void draw();

        // Proxy methods to ensure that both the game loop and state loop
        // methods are called (particularly to ensure that derived classes
        // can't change this behavior)
        void masterEvent(sf::Event a_event);
        void masterTick();
        void masterDraw();

        void maintainAspectRatio(sf::View& view, sf::RenderWindow& window);

        CenteredSprite screenSprite;
        sf::View screenView;

        std::stack<std::unique_ptr<GameState>> states;
        bool running;
};

#endif
