#include "Generic.h"
#include <iostream>



Generic::Generic (const sf::Vector2f& position, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Generic::setSpriteAttributes(sf::Sprite& sprited, const sf::Texture& texture, const sf::Vector2f& position) {
    sprited.setTexture(texture);
    sprited.setPosition(position);
}

sf::Vector2f Generic::getPosition() const {
    return sprite.getPosition();
}
void Generic::setPosition(const sf::Vector2f& position) { // Fixed scope
    sprite.setPosition(position);
}

void Generic::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

