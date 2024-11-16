#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"

class Level {
private:
    sf::RenderWindow& window;
    std::vector<sf::Drawable*> drawables;
    Player player;

public:
    Level(sf::RenderWindow& window);
    void setup();
    void run(float dt);
};

#endif
