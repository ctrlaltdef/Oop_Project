#ifndef GENERIC_H
#define GENERIC_H

#include <SFML/Graphics.hpp>

// Generic class serves as a base class for drawable objects with a sprite
class Generic {
protected:
    sf::Sprite sprite;  // Sprite used to represent the object graphically

public:
    Generic() = default;  // Default constructor
    Generic(const sf::Vector2f& position, const sf::Texture& texture);  // Constructor to initialize position and texture

    virtual void setPosition(const sf::Vector2f& position);  // Sets the sprite's position
    void setSpriteAttributes(sf::Sprite& sprite, const sf::Texture& texture, const sf::Vector2f& position);  // Utility to configure sprite attributes
    virtual sf::Vector2f getPosition() const;  // Retrieves the sprite's position
    virtual void draw(sf::RenderWindow& window);  // Draws the sprite on the provided window

    virtual ~Generic() = default;  // Virtual destructor for proper cleanup of derived classes
};

#endif
