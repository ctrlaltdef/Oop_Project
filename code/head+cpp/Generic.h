#ifndef GENERIC_H
#define GENERIC_H

#include <SFML/Graphics.hpp>


class Generic {
protected:
    sf::Sprite sprite;

public:
    Generic() = default;
    Generic(const sf::Vector2f& position, const sf::Texture& texture);

    virtual void setPosition(const sf::Vector2f& position);
    void setSpriteAttributes(sf::Sprite& sprite, const sf::Texture& texture, const sf::Vector2f& position);
    virtual sf::Vector2f getPosition() const;
    virtual void draw(sf::RenderWindow& window);
    virtual ~Generic() = default;
};

#endif
