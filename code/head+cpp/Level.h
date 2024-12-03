#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Overlay.h"
#include "Sky.h"
#include "SoilLayer.h"
#include "Market.h"

class Level {
public:
    Level(sf::RenderWindow& window);
    void setup();
    void run(float dt);
    void handleMarketInteraction();
    void checkMarketProximity();

private:
    sf::RenderWindow& window;
    sf::View camera;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    float groundWidth = 0.0f;
    float groundHeight = 0.0f;

    Player player;
    Overlay overlay;
    SoilLayer soilLayer;
    Sky sky;
    std::vector<sf::Drawable*> drawables;
    Market market;

    bool marketActive;
};

#endif
