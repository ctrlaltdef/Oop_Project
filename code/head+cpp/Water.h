#ifndef WATER_H
#define WATER_H

#include "Generic.h"
#include <vector>

class Water : public Generic {
private:
    std::vector<sf::Texture> frames; // Animation frames
    float frameIndex;

public:
    Water(const std::vector<sf::Texture>& frames, const sf::Vector2f& position, int zIndex);
    void update(float dt) override;
};

#endif
