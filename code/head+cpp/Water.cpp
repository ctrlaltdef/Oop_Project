#include "Water.h"
#include <iostream>
 

Water::Water(const std::vector<sf::Texture>& frames, const sf::Vector2f& position, int zIndex)
    : Generic(frames[0], position, zIndex), frames(frames), frameIndex(0) {}

void Water::update(float dt) {
    frameIndex += 5 * dt;
    if (frameIndex >= frames.size()) {
        frameIndex = 0;
    }
    sprite.setTexture(frames[static_cast<int>(frameIndex)]);
}











