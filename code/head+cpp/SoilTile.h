#ifndef SOILTILE_H
#define SOILTILE_H

#include "Generic.h"  // Include base class header for Generic

class SoilTile : public Generic {
public:
    // Constructor to initialize position and texture for the soil tile
    SoilTile(const sf::Vector2f& position, sf::Texture& texture);

    // Getter for the position of the soil tile
    sf::Vector2f getPosition() const;

    // Method to draw the soil tile to the window
    void draw(sf::RenderWindow& window);

    // Default destructor (no additional resources to release)
    ~SoilTile() = default;
};

#endif
