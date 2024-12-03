#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>  // SFML library for graphics
#include "Level.h"  // Include Level class for game logic

// Game class that encapsulates the main game loop and window
class Game {
private:
    sf::RenderWindow window;  // The game window
    Level level;  // The game level, handles game logic and rendering

public:
    Game();  // Constructor to initialize the game
    void run();  // Method to start and run the main game loop
};

#endif
