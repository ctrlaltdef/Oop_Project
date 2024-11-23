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
#include "Sky.h"

class Level {
private:
    sf::RenderWindow& window;
    std::vector<Generic*> elements; 
    Player player;
    Sky sky;
    Overlay overlay;
    sf::Sprite background; 
    sf::Texture backgroundTexture; 
    std::vector<sf::Drawable*> drawables;

public:
    Level(sf::RenderWindow& window);
    void setup();
    void reset(sf::RenderWindow& window);
    void run(float dt);

};

#endif


