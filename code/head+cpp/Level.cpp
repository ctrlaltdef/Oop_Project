#include "Level.h"
#include <cmath>

Level::Level(sf::RenderWindow& window)
    : window(window), player(sf::Vector2f(500, 300), window), overlay(window, &player), sky(window), market(), marketActive(false) {
    setup();
    camera.setSize(static_cast<sf::Vector2f>(window.getSize()));
    camera.setCenter(player.getPosition());
}

void Level::setup() {
    backgroundTexture.loadFromFile("../graphics/world/ground1.png");
    background.setTexture(backgroundTexture);

    float scaleFactor = 0.8f;
    background.setScale(scaleFactor, scaleFactor);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    groundWidth = textureSize.x * scaleFactor;
    groundHeight = textureSize.y * scaleFactor;

    background.setPosition(0, 0);
    player.setPosition(sf::Vector2f(groundWidth / 2.0f, groundHeight / 2.0f));

    drawables.push_back(&background);

    soilLayer = SoilLayer();
    player.setSoilLayer(&soilLayer);
}

template <typename T>
T clamp(const T& value, const T& min, const T& max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void Level::run(float dt) {
    player.update(dt);
    checkMarketProximity();

    sf::Vector2f playerPos = player.getPosition();
    float playerWidth = player.getSprite().getGlobalBounds().width;
    float playerHeight = player.getSprite().getGlobalBounds().height;

    playerPos.x = clamp(playerPos.x, 0.0f, groundWidth - playerWidth);
    playerPos.y = clamp(playerPos.y, 0.0f, groundHeight - playerHeight);
    player.setPosition(playerPos);

    sf::Vector2f viewCenter = player.getPosition();
    sf::Vector2f viewSize = camera.getSize();

    viewCenter.x = clamp(viewCenter.x, viewSize.x / 2, groundWidth - viewSize.x / 2);
    viewCenter.y = clamp(viewCenter.y, viewSize.y / 2, groundHeight - viewSize.y / 2);

    camera.setCenter(viewCenter);
    window.setView(camera);

    window.clear(sf::Color::Black);

    for (auto& drawable : drawables) {
        window.draw(*drawable);
    }

    soilLayer.draw(window);
    player.draw(window);

    if (marketActive) {
        market.render(window, player.getInventory(), player.getMoney());
        handleMarketInteraction();
    }

    overlay.display(camera);
    sky.display(dt);

    window.display();
}

void Level::checkMarketProximity() {
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f marketPos(700, 300);

    float distance = std::sqrt(std::pow(playerPos.x - marketPos.x, 2) +
                               std::pow(playerPos.y - marketPos.y, 2));

    if (distance < 100.0f && sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        marketActive = true;
    } else if (marketActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        marketActive = false;
    }
}

void Level::handleMarketInteraction() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        market.buyItem("Corn Seed", 1, player);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        market.sellItem("Corn Crop", 1, player);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        market.buyItem("Tomato Seed", 1, player);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        market.sellItem("Tomato Crop", 1, player);
    }
}
