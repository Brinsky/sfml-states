#include "VirtualScreen.h"

VirtualScreen::VirtualScreen(unsigned int width, unsigned int height)
{
    create(width, height);
    initialize();
}

/// Draws the sprite at a given location in the game world. This location is
/// dependent on the implementation within a VirtualScreen subclass.
void VirtualScreen::worldDraw(sf::Sprite& sprite, const sf::Vector2f& position)
{
    // The sprite's old positon doesn't matter, but it will be restored after
    // drawing
    const sf::Vector2f& oldPosition = sprite.getPosition();
    
    // Perform a class-specific conversion from world coordinates to pixel
    // coordinates
    sprite.setPosition(getPixelPosition(position));
    draw(sprite);
    
    // Restore the old position
    sprite.setPosition(oldPosition);
}

/// Draws the sprite at an exact pixel location on the VirtualScreen
void VirtualScreen::pixelDraw(sf::Sprite& sprite, const sf::Vector2f& position)
{
    // The sprite's old positon doesn't matter, but it will be restored after
    // drawing
    const sf::Vector2f& oldPosition = sprite.getPosition();
    
    sprite.setPosition(position);
    draw(sprite);
    
    // Restore the old position
    sprite.setPosition(oldPosition);
}

/// Converts a game world positon into an absolute pixel position. This
/// position is dependent on class'/subclass' implementation.
sf::Vector2f VirtualScreen::getPixelPosition(const sf::Vector2f& worldPosition)
{
    return worldPosition;
}
