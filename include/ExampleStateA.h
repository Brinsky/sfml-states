#ifndef EXAMPLESTATEA_H
#define EXAMPLESTATEA_H

#include "GameState.h"

class ExampleStateA : public GameState
{
    public:
        ExampleStateA(Game& a_game, sf::Font& font);
        virtual ~ExampleStateA();

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

#endif // EXAMPLESTATEA_H
