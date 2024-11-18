#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Settings.h"
#include "Overlay.h"
#include "Generic.h"
#include "Water.h"
#include "WildFlower.h"
#include "Tree.h"

class Level {
private:
    sf::RenderWindow& window;
    std::vector<Generic*> elements; 
    Player player;
    Overlay overlay;
    sf::Sprite background; // Background sprite
    sf::Texture backgroundTexture; // Background texture
    std::vector<sf::Drawable*> drawables;

public:
    Level(sf::RenderWindow& window);
    void setup();
    void run(float dt);
};

#endif


