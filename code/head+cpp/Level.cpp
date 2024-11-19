#include "Level.h"
#include <iostream>
#include "Settings.h"
#include "Generic.h"
#include "Water.h"
#include "WildFlower.h"
#include "Tree.h"

Level::Level(sf::RenderWindow& window)
    : window(window), player(sf::Vector2f(540, 300)), overlay(&player) {
    setup();
}

void Level::setup() {
    if (!backgroundTexture.loadFromFile("../graphics/world/ground.png")) {
        std::cerr << "Error: Cant load background texture!" << std::endl;
    }
    background.setTexture(backgroundTexture);
    float scaleFactor = 0.4f; 
    background.setScale(scaleFactor, scaleFactor);

    sf::Vector2u backgroundSize = backgroundTexture.getSize();
    sf::Vector2f scaledSize(backgroundSize.x * scaleFactor, backgroundSize.y * scaleFactor);
    sf::Vector2u screenSize = window.getSize();
    float centerX = (screenSize.x / 2.0f) - (scaledSize.x / 2.0f);
    float centerY = (screenSize.y / 2.0f) - (scaledSize.y / 2.0f);
    background.setPosition(centerX, centerY);

    drawables.push_back(&background); 
    drawables.push_back(&player.getSprite()); 
    
    sf::Texture flowerTexture;
    if (!flowerTexture.loadFromFile("../graphics/objects/sunflower.png")) {
        std::cerr << "Error loading flower texture!" << std::endl;
    }
    WildFlower* flower = new WildFlower(flowerTexture, sf::Vector2f(400, 400), LAYERS.at("main"));
    elements.push_back(flower);

    sf::Texture treeTexture;
    if (!treeTexture.loadFromFile("../graphics/objects/tree_medium.png")) {
        std::cerr << "Error loading tree texture!" << std::endl;
    }
    Tree* tree = new Tree(treeTexture, sf::Vector2f(500, 300), LAYERS.at("main"));
    elements.push_back(tree);

    std::vector<sf::Texture> waterFrames;
    for (int i = 0; i < 4; ++i) {
        sf::Texture waterFrame;
        if (waterFrame.loadFromFile("../graphics/water/" + std::to_string(i) + ".png")) {
            waterFrames.push_back(waterFrame);
        }
    }
    Water* water = new Water(waterFrames, sf::Vector2f(780, 75), LAYERS.at("water"));
    elements.push_back(water);
}

void Level::run(float dt) {
    window.clear(sf::Color::Black);

    for (auto& drawable : drawables) {
        window.draw(*drawable);
    }

    std::sort(elements.begin(), elements.end(), [](Generic* a, Generic* b) {
        return a->z < b->z; 
    });

    for (auto element : elements) {
        element->update(dt);0
        window.draw(*element); 
    }

    player.update(dt);
    overlay.display(window);
    window.display();
}








