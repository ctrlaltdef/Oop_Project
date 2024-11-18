#include "Generic.h"
#include <cmath>
#include <iostream>
using namespace std;


Generic::Generic(const sf::Texture& texture, const sf::Vector2f& position, int zIndex)
    : z(zIndex) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Generic::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}


void Generic::update(float dt) {
}

