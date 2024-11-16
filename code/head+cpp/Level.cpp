#include "Level.h"

Level::Level(sf::RenderWindow& window) 
    : window(window), player(sf::Vector2f(540, 300)) { // Initial player position
    setup();
}

void Level::setup() {
}

void Level::run(float dt) {
    window.clear(sf::Color::Black);

    for (auto& drawable : drawables) {
        window.draw(*drawable);
    }

    player.update(dt);
    player.draw(window);

    window.display();
}
