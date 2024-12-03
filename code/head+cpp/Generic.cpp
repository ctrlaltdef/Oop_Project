#include "Generic.h"
#include <iostream>

// Constructor initializes the sprite with a texture and position
Generic::Generic(const sf::Vector2f& position, const sf::Texture& texture) {
    sprite.setTexture(texture);  // Assign the provided texture to the sprite
    sprite.setPosition(position);  // Set the sprite's position
}

// Utility function to configure a sprite's texture and position
void Generic::setSpriteAttributes(sf::Sprite& sprited, const sf::Texture& texture, const sf::Vector2f& position) {
    sprited.setTexture(texture);  // Assign texture
    sprited.setPosition(position);  // Assign position
}

// Returns the position of the sprite
sf::Vector2f Generic::getPosition() const {
    return sprite.getPosition();  // Get sprite's position
}

// Sets the position of the sprite
void Generic::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);  // Update sprite's position
}

// Draws the sprite on the window
void Generic::draw(sf::RenderWindow& window) {
    window.draw(sprite);  // Render the sprite to the provided window
}
