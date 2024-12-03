#include "Game.h"
#include "Level.h"

// Constructor initializes the game window and sets the frame rate
Game::Game() 
    : window(sf::VideoMode(1280, 720), "Fields Of Fortune"),  // Set window size and title
      level(window)  // Initialize level with the game window
{
    window.setFramerateLimit(30);  // Limit the frame rate to 30 FPS
}

// Main game loop
void Game::run() {
    sf::Clock clock;  // Clock to measure time between frames

    // Game loop runs while the window is open
    while (window.isOpen()) {
        sf::Event event;  // Event object to handle window events

        // Poll events from the window
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {  // Check if the window is closed
                window.close();  // Close the window
            }
        }

        float dt = clock.restart().asSeconds();  // Calculate delta time (time elapsed since last frame)
        level.run(dt);  // Update and render the game level
    }
}
