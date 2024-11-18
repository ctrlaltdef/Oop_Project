#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Level.h"

class Game {
private:
    sf::RenderWindow window;
    Level level;

public:
    Game();
    void run();
};

#endif


