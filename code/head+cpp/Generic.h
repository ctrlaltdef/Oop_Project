#ifndef GENERIC_H
#define GENERIC_H

#include <SFML/Graphics.hpp>


class Generic : public sf::Drawable {
protected:
    sf::Sprite sprite;
    
public:
    int z; 
    Generic(const sf::Texture& texture, const sf::Vector2f& position, int zIndex);
    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    
};

#endif







