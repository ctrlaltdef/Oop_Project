
#ifndef SOILTILE_H
#define SOILTILE_H

#include "Generic.h"

class SoilTile : public Generic {
public:
    SoilTile(const sf::Vector2f& position, sf::Texture& texture);
    sf::Vector2f getPosition() const;
    void draw(sf::RenderWindow& window);
    ~SoilTile() = default;
};

#endif
