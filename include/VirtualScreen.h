#ifndef VIRTUALSCREEN_H
#define VIRTUALSCREEN_H

#include <SFML/Graphics.hpp>

class VirtualScreen : public sf::RenderTexture
{
    public:
        VirtualScreen(unsigned int width, unsigned int height);
        void worldDraw(sf::Sprite& sprite, const sf::Vector2f& position);
        void pixelDraw(sf::Sprite& sprite, const sf::Vector2f& position);

    private:
        virtual sf::Vector2f getPixelPosition(const sf::Vector2f& worldPos);
};

#endif
