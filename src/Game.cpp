#include "Game.h"

#include <iostream>

#include "GameState.h"

Game::Game(sf::RenderWindow& a_window, VirtualScreen& a_screen) :
    window(a_window),
    screen(a_screen),
    screenSprite(screen.getTexture()),
    screenView(sf::Vector2f(0, 0), sf::Vector2f(screen.getSize().x,
                                                screen.getSize().y))
{
    // The maintainAspectRatio() method requires the sprite in question to be
    // centered
    screenSprite.setOrigin(float(screenSprite.getTextureRect().width / 2.0),
                           float(screenSprite.getTextureRect().height / 2.0));

    screenSprite.setTextureRect(sf::IntRect(0,
                                            screen.getSize().y,
                                            screen.getSize().x,
                                            -screen.getSize().y));

    maintainAspectRatio(screenView, window);
    running = true;
}

/// Cleans up both game and state related data
Game::~Game()
{
    // Empty the stack of GameStates and properly destroy the GameStates
    while (!states.empty())
        states.pop();

    window.close();
}

/// Loops all major game methods while the game is running. The "master"
/// methods ensure that any child of Game still calls all of its own and
/// its GameStates' major game methods.
void Game::loop()
{
    sf::Event event;

    while (running)
    {
        while (window.pollEvent(event))
            masterEvent(event);

        masterTick();
        masterDraw();
    }
}

//~--- State stack management methods

/// Pop the current GameState and push a new one
void Game::changeState(std::unique_ptr<GameState> state)
{
    if (!states.empty())
        states.pop();

    pushState(std::move(state));
}

/// Push a GameState onto the stack
void Game::pushState(std::unique_ptr<GameState> state)
{
    if (!states.empty())
        states.top()->pause();

    // GameStates start paused and must be resumed
    state->resume();

    states.push(std::move(state));
}

/// Pop a GameState off of the stack
void Game::popState()
{
    if (!states.empty())
    {
        states.pop();
        states.top()->resume(); // Resume previous state
    }
}

//~--- Lifetime methods

/// Signals the intention to exit the game at the next opportunity
void Game::quit()
{
    running = false;
}

//~--- Game specific loop methods (should not call state loop functions!)

/// Responds to any Game-level SFML events
void Game::event(sf::Event a_event)
{
    // Handle window exit. Derived classes can call quit().
    if (a_event.type == sf::Event::Closed)
        running = false;

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
    
}

//~--- Proxy loop methods

/// Handles events for both the Game and it's current GameState
void Game::masterEvent(sf::Event a_event)
{
    // Ensures that the virtual screen is kept at the proper size and
    // aspect ratio within the RenderWindow
    if (a_event.type == sf::Event::Resized)
        maintainAspectRatio(screenView, window);

    event(a_event);

    if (!states.empty())
        states.top()->event(a_event);
}

/// Performs actions for both the Game and it's current GameState
void Game::masterTick()
{
    tick();

    if (!states.empty())
        states.top()->tick();
}

/// Draws both the Game and it's current GameState
void Game::masterDraw()
{
    screen.clear();

    draw();

    // Pass any GameStates our virtual screen to draw on. They will have no
    // knowledge of the actual window.
    if (!states.empty())
        states.top()->draw(screen);

    // Draw our virtual screen onto our real window. The view established by
    // maintainAspectRatio() will ensure proper size, ratio, and positioning
    window.clear();
    window.draw(screenSprite);
    window.display();
}

//~--- Drawing helper methods

/// Maintains the aspect ratio of a given view while making it as large as
/// possible within the given window. The number of pixels (width and height)
/// displayed by the view remains unchanged. The view is also centered in the
/// window.
void Game::maintainAspectRatio(sf::View& view, sf::RenderWindow& window)
{
    // sf::View.getSize() returns a Vector2f, this is float division
    float viewRatio = view.getSize().x / view.getSize().y;
    float winRatio = ((float) window.getSize().x) / window.getSize().y;

    float viewWidthFrac;
    float viewHeightFrac;

    // Determine the ratios of viewport size to window size which will
    // maintain the viewport's aspect ratio
    if (winRatio > viewRatio)
    {
        // If the view is "narrower" in ratio than the window
        viewWidthFrac = viewRatio / winRatio;
        viewHeightFrac = 1.0f; // It's height will match the window's height
    }
    else
    {
        // If the view is "shorter" in ratio than the window
        viewWidthFrac = 1.0f; // It's width will match the windows width
        viewHeightFrac = winRatio / viewRatio;
    }

    // Find where the top left corner of the viewport should be in order to
    // center it 
    float xPos = 0.5f - (viewWidthFrac / 2.0f);
    float yPos = 0.5f - (viewHeightFrac / 2.0f);

    // Setting the viewport allows us to map a view to a window at a specific
    // location and proportion
    view.setViewport(sf::FloatRect(xPos, yPos, viewWidthFrac, viewHeightFrac));
    window.setView(view);
}
