#ifndef SOIL_TILE_H
#define SOIL_TILE_H

#include <SFML/Graphics.hpp>

class SoilTile {
public:
    SoilTile(const sf::Vector2f& position, sf::Texture& texture);

    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
};

#endif
