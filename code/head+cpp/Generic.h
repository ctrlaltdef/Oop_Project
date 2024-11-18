#ifndef GENERIC_H
#define GENERIC_H

#include <SFML/Graphics.hpp>


class Generic : public sf::Drawable {
protected:
    sf::Sprite sprite;
    
public:
    int z; // Z-index for rendering order
    Generic(const sf::Texture& texture, const sf::Vector2f& position, int zIndex);
    virtual void update(float dt);
    // Override the draw method from sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


    
};

#endif







