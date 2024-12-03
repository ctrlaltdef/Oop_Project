#include "Player.h"
#include <cmath>
#include <iostream>
using namespace std;

// Constructor initializes the player with starting position, default attributes, and timers
Player::Player(const sf::Vector2f &startPos, sf::RenderWindow& window)
    : speed(200.0f), frameIndex(0), toolIndex(0), seedIndex(0), position(startPos), money(200) 
{
    // Default status and direction
    status = "down_idle";
    direction = sf::Vector2f(0, 0);

    // Initialize tools and seeds
    tools = {"hoe", "axe", "water"};
    selectedTool = tools[toolIndex];

    seeds = {"corn", "tomato"};
    selectedSeed = seeds[seedIndex];

    // Initialize timers for tool and seed usage and switching
    timers["tool use"] = Timer(350, [&]() { useTool(); });
    timers["tool switch"] = Timer(200, []() {});
    timers["seed use"] = Timer(350, [&]() { useSeed(window); });
    timers["seed switch"] = Timer(200, []() {});

    // Import all animation assets
    importAssets();

    // Set initial sprite texture and position
    sprite.setTexture(animations[status][frameIndex]);
    sprite.setPosition(position);
}

// Import all animation assets for various player states
void Player::importAssets()
{
    std::vector<std::string> directions = {
        "up", "down", "left", "right",
        "up_idle", "down_idle", "left_idle", "right_idle",
        "up_hoe", "down_hoe", "left_hoe", "right_hoe",
        "up_axe", "down_axe", "left_axe", "right_axe",
        "up_water", "down_water", "left_water", "right_water"};

    for (const auto &dir : directions) {
        animations[dir] = importFolder("../graphics/character/" + dir);
    }

    // Handle missing animation frames
    if (!animations[status].empty()) {
        sprite.setTexture(animations[status][frameIndex]);
    } else {
        std::cout << "Error: No frames for status " << status << std::endl;
    }
}

// Update animation frames based on the elapsed time
void Player::animate(float dt)
{
    frameIndex += 29.4 * dt; // Speed up animation
    if (frameIndex >= animations[status].size()) {
        frameIndex = 0; // Loop back to the first frame
    }
    sprite.setTexture(animations[status][frameIndex]);
}

// Handle keyboard input for player movement, tool, and seed interactions
void Player::handleInput()
{
    if (!timers["tool use"].isActive()) {
        direction = sf::Vector2f(0, 0);

        // Movement input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction.y = -1;
            status = "up";
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction.y = 1;
            status = "down";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction.x = -1;
            status = "left";
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction.x = 1;
            status = "right";
        }

        // Tool usage input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            timers["tool use"].activate();
            direction = sf::Vector2f(0, 0);
            frameIndex = 0;
        }

        // Tool switch input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && !timers["tool switch"].isActive()) {
            timers["tool switch"].activate();
            toolIndex = (toolIndex + 1) % tools.size();
            selectedTool = tools[toolIndex];
        }

        // Seed usage input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            timers["seed use"].activate();
            direction = sf::Vector2f(0, 0);
            frameIndex = 0;
        }

        // Seed switch input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !timers["seed switch"].isActive()) {
            timers["seed switch"].activate();
            seedIndex = (seedIndex + 1) % seeds.size();
            selectedSeed = seeds[seedIndex];
        }
    }
}

// Determine player status based on movement or interactions
void Player::getStatus()
{
    if (direction == sf::Vector2f(0, 0)) {
        status = status.substr(0, status.find("_")) + "_idle";
    }
    if (timers["tool use"].isActive()) {
        status = status.substr(0, status.find("_")) + "_" + selectedTool;
    }
    if (timers["seed use"].isActive()) {
        status = status.substr(0, status.find("_")) + "_" + selectedSeed;
    }
}

// Update player position based on direction and speed
void Player::move(float dt)
{
    if (std::sqrt(direction.x * direction.x + direction.y * direction.y) > 0) {
        direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y); // Normalize direction
    }

    // Update position
    position.x += direction.x * speed * dt;
    sprite.setPosition(position.x, sprite.getPosition().y);

    position.y += direction.y * speed * dt;
    sprite.setPosition(sprite.getPosition().x, position.y);
}

// Update all active timers
void Player::updateTimers()
{
    for (auto &timer : timers) {
        timer.second.update();
    }
}

// Main update method for the player
void Player::update(float dt)
{
    handleInput();      // Handle input
    getStatus();        // Update status
    updateTimers();     // Update timers

    // Calculate target position for tools and seeds
    sf::Vector2f offset;
    if (status.find("up") != std::string::npos) offset = {0, -10};
    else if (status.find("down") != std::string::npos) offset = {0, 50};
    else if (status.find("left") != std::string::npos) offset = {-50, 40};
    else if (status.find("right") != std::string::npos) offset = {50, 40};

    targetPosition = sprite.getPosition() + offset;
    targetPosition.x = std::round(targetPosition.x / 64) * 64; // Snap to grid
    targetPosition.y = std::round(targetPosition.y / 64) * 64;

    move(dt);           // Move player
    animate(dt);        // Animate player
}

// Render the player sprite to the window
void Player::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

// Use the selected tool at the target position
void Player::useTool()
{
    if (selectedTool == "hoe" && soilLayer) {
        soilLayer->getHit(targetPosition); // Hoe functionality
    } else if (selectedTool == "water" && soilLayer) {
        soilLayer->water(targetPosition, getSelectedSeed()); // Water functionality
    } else if (selectedTool == "axe" && soilLayer) {
        soilLayer->harvest(targetPosition, *this); // Harvest functionality
    }
}

// Use the selected seed at the target position
void Player::useSeed(sf::RenderWindow& window)
{
    if (selectedSeed != "" && soilLayer) {
        soilLayer->plant_seeds(targetPosition, selectedSeed, *this, window);
    }
}

// Getters and setters for player attributes
std::string Player::getSelectedSeed() const { return selectedSeed; }
std::string Player::getSelectedTool() const { return selectedTool; }
const std::vector<std::string>& Player::getSeeds() const { return seeds; }
const std::vector<std::string>& Player::getTools() const { return tools; }
sf::Sprite& Player::getSprite() { return sprite; }
sf::Vector2f Player::getPosition() const { return sprite.getPosition(); }
void Player::setPosition(const sf::Vector2f& position) { sprite.setPosition(position); }
Inventory& Player::getInventory() { return inventory; }
int& Player::getMoney() { return money; }
void Player::addMoney(int amount) { money += amount; }
void Player::deductMoney(int amount) { if (money >= amount) money -= amount; }
