#include "Game.h"
#include "Level.h"

Game::Game() : window(sf::VideoMode(1280, 720), "Fields Of Fortune"), level(window) {
    window.setFramerateLimit(60);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();
        level.run(dt);
    }
}


