#ifndef EXAMPLESTATEB_H
#define EXAMPLESTATEB_H

#include "GameState.h"

class ExampleStateB : public GameState
{
    public:
        ExampleStateB(Game& a_game, sf::Font& font);
        virtual ~ExampleStateB();

        void pause();
        void resume();

        void event(sf::Time elapsed, sf::Event a_event);
        void update(sf::Time elapsed);
        void draw(VirtualScreen& screen);

    private:
        sf::CircleShape shape;
        sf::Font& font;
        sf::Text text;
        sf::Text pressSpace;
};

#endif // EXAMPLESTATEB_H
