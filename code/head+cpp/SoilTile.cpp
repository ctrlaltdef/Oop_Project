#include "SoilTile.h"

SoilTile::SoilTile(const sf::Vector2f& position, sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}
sf::Vector2f SoilTile::getPosition() const {
    return sprite.getPosition();
}
void SoilTile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
