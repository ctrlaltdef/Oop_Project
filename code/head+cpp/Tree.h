#ifndef TREE_H
#define TREE_H

#include "Generic.h"

class Tree : public Generic {
public:
    Tree(const sf::Texture& texture, const sf::Vector2f& position, int zIndex);
};

#endif
