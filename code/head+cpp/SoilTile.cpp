#include "SoilTile.h" 

// Constructor: Initializes the position and texture for the soil tile by calling the base class constructor
SoilTile::SoilTile(const sf::Vector2f& position, sf::Texture& texture) 
    : Generic(position, texture) {}

// Getter for the position of the soil tile (returns the position of the sprite)
sf::Vector2f SoilTile::getPosition() const {
    return sprite.getPosition();  // Retrieve position of the sprite (inherited from Generic)
}

// Method to draw the soil tile to the window
void SoilTile::draw(sf::RenderWindow& window) {
    window.draw(sprite);  // Draw the sprite to the window
}
