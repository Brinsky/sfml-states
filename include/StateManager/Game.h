#ifndef GAME_H
#define GAME_H

#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "VirtualScreen.h"

// Forward declaration, required to prevent circular dependency
class GameState;

/// A Game manages an SFML window, SFML events, and GameStates.
/// The structure of Game was partly inspired by this post:
/// http://gamedevgeek.com/tutorials/managing-game-states-in-c/
class Game
{
    public:
        Game(sf::RenderWindow& a_window, VirtualScreen& a_screen);
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
        VirtualScreen& screen;

    private:
        // Game loop methods, called in this order
        virtual void event(sf::Time elapsed, sf::Event a_event);
        virtual void update(sf::Time elapsed);
        virtual void draw();

        // Proxy methods to ensure that both the game loop and state loop
        // methods are called (particularly to ensure that derived classes
        // can't change this behavior)
        void masterEvent(sf::Time elapsed, sf::Event a_event);
        void masterUpdate(sf::Time elapsed);
        void masterDraw();

        void maintainAspectRatio(sf::View& view, sf::RenderWindow& window);

        sf::Sprite screenSprite;
        sf::View screenView;

        std::stack<std::unique_ptr<GameState>> states;
        bool running;
};

#endif
