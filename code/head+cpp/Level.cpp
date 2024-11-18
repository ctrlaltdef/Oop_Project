#include "Level.h"
#include <iostream>
#include "Settings.h"
#include "Generic.h"
#include "Water.h"
#include "WildFlower.h"
#include "Tree.h"

// Level::Level(sf::RenderWindow& window)
//     : window(window), player(sf::Vector2f(540, 300)), overlay(&player) { // Initialize overlay with a pointer to player
//     setup();
// }

// void Level::setup() {
//     // Load the background texture
//     if (!backgroundTexture.loadFromFile("../graphics/world/ground.png")) {
//         std::cerr << "Error: Could not load background texture!" << std::endl;
//     }
//     background.setTexture(backgroundTexture);
//     float scaleFactor = 0.4f; 
//     background.setScale(scaleFactor, scaleFactor);

//     // Calculate the scaled size of the background
//     sf::Vector2u backgroundSize = backgroundTexture.getSize();
//     sf::Vector2f scaledSize(backgroundSize.x * scaleFactor, backgroundSize.y * scaleFactor);

//     // Get the screen size
//     sf::Vector2u screenSize = window.getSize();

//     // Calculate the center position of the scaled background
//     float centerX = (screenSize.x / 2.0f) - (scaledSize.x / 2.0f);
//     float centerY = (screenSize.y / 2.0f) - (scaledSize.y / 2.0f);

//     // Set the background position to center it
//     background.setPosition(centerX, centerY);

//     // Add background and player to drawables for rendering in order
//     drawables.push_back(&background); // Background at the bottom layer
 
//     // Load tree texture
//     sf::Texture treeTexture;
//     if (!treeTexture.loadFromFile("../graphics/objects/tree_medium.png")) {
//         std::cerr << "Error loading tree texture!" << std::endl;
//     }
//     Tree* tree = new Tree(treeTexture, sf::Vector2f(200, 300), LAYERS.at("main"));
//     elements.push_back(tree);
//     drawables.push_back(tree); // Add Tree to drawables

//     // Load flower texture
//     sf::Texture flowerTexture;
//     if (!flowerTexture.loadFromFile("../graphics/objects/sunflower.png")) {
//         std::cerr << "Error loading flower texture!" << std::endl;
//     }
//     WildFlower* flower = new WildFlower(flowerTexture, sf::Vector2f(400, 400), LAYERS.at("main"));
//     elements.push_back(flower);
//     drawables.push_back(flower); // Add WildFlower to drawables

//     // Load water textures
//     std::vector<sf::Texture> waterFrames;
//     for (int i = 0; i < 4; ++i) {
//         sf::Texture waterFrame;
//         if (waterFrame.loadFromFile("../graphics/water/" + std::to_string(i) + ".png")) {
//             waterFrames.push_back(waterFrame);
//         }
//     }
//     Water* water = new Water(waterFrames, sf::Vector2f(600, 400), LAYERS.at("water"));
//     elements.push_back(water);
//     drawables.push_back(water); // Add Water to drawables

//     drawables.push_back(&player.getSprite()); // Player on top

// }



void Level::run(float dt) {
    window.clear(sf::Color::White);
    
    for (auto& drawable : drawables) {
        window.draw(*drawable);
    }

    // Sort elements by their z-index before drawing
    std::sort(elements.begin(), elements.end(), [](Generic* a, Generic* b) {
        return a->z < b->z; // Lower z-index elements are drawn first
    });

    // Update and draw all elements
    for (auto element : elements) {
        element->update(dt);
        element->draw(window, sf::RenderStates::Default);
    }
    player.update(dt);
    overlay.display(window);
    window.display();

}





// #include "Level.h"
// #include <iostream>
// #include "Settings.h"
// #include "Generic.h"
// #include "Water.h"
// #include "WildFlower.h"
// #include "Tree.h"

Level::Level(sf::RenderWindow& window)
    : window(window), player(sf::Vector2f(540, 300)), overlay(&player) { // Initialize overlay with a pointer to player
    setup();
}

void Level::setup() {
    // Load the background texture
    if (!backgroundTexture.loadFromFile("../graphics/world/ground.png")) {
        std::cerr << "Error: Could not load background texture!" << std::endl;
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

    // Add background and player to drawables for rendering in order
    drawables.push_back(&background); // Background at the bottom layer
    drawables.push_back(&player.getSprite()); // Player on top

    // Load and add WildFlower
    sf::Texture flowerTexture;
    if (!flowerTexture.loadFromFile("../graphics/objects/sunflower.png")) {
        std::cerr << "Error loading flower texture!" << std::endl;
    }
    WildFlower* flower = new WildFlower(flowerTexture, sf::Vector2f(400, 400), LAYERS.at("main"));
    elements.push_back(flower);

    // Load and add Tree
    sf::Texture treeTexture;
    if (!treeTexture.loadFromFile("../graphics/objects/tree_medium.png")) {
        std::cerr << "Error loading tree texture!" << std::endl;
    }
    Tree* tree = new Tree(treeTexture, sf::Vector2f(500, 300), LAYERS.at("main"));
    elements.push_back(tree);

    // Load and add Water
    std::vector<sf::Texture> waterFrames;
    for (int i = 0; i < 4; ++i) {
        sf::Texture waterFrame;
        if (waterFrame.loadFromFile("../graphics/water/" + std::to_string(i) + ".png")) {
            waterFrames.push_back(waterFrame);
        }
    }
    Water* water = new Water(waterFrames, sf::Vector2f(600, 400), LAYERS.at("water"));
    elements.push_back(water);
}

void Level::run(float dt) {
    window.clear(sf::Color::Blue);

    // Draw all drawable objects
    for (auto& drawable : drawables) {
        window.draw(*drawable);
    }

    // Sort elements by their z-index before drawing
    std::sort(elements.begin(), elements.end(), [](Generic* a, Generic* b) {
        return a->z < b->z; // Lower z-index elements are drawn first
    });

    // Update and draw all elements
    for (auto element : elements) {
        element->update(dt);
        window.draw(*element); // Draw directly
    }

    player.update(dt);
    overlay.display(window);
    window.display();
}








