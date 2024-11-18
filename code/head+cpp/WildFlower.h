#ifndef WILDFLOWER_H
#define WILDFLOWER_H

#include "Generic.h"

class WildFlower : public Generic {
public:
    WildFlower(const sf::Texture& texture, const sf::Vector2f& position, int zIndex);
};


#endif