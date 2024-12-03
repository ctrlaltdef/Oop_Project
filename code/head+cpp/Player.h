#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include "Timer.h"
#include "SoilLayer.h"
#include "Inventory.h"
#include "Support.h"
// Class representing the Player entity in the game
class Player {
private:
    // Player's graphical representation
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed; // Player's movement speed

    // Animation management
    std::map<std::string, std::vector<sf::Texture>> animations;
    std::string status; // Current animation state
    int frameIndex; // Current animation frame

    // Gameplay mechanics
    SoilLayer* soilLayer; // Reference to the soil layer
    sf::Vector2f targetPosition; // Position for targeted actions
    Inventory inventory; // Player's inventory
    int money; // Player's in-game currency

    // Tools and seeds
    std::vector<std::string> tools;
    int toolIndex;
    std::string selectedTool;

    std::vector<std::string> seeds;
    int seedIndex;
    std::string selectedSeed;

    // Timers for actions
    std::map<std::string, Timer> timers;

    // Private utility methods
    void importAssets();
    void animate(float dt);
    void move(float dt);
    void updateTimers();
    void getStatus();
    void useTool();
    void useSeed(sf::RenderWindow& window);

public:
    Player(const sf::Vector2f& startPos, sf::RenderWindow& window);

    // Input and update methods
    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);

    // Accessors and mutators
    void setSoilLayer(SoilLayer* layer) { soilLayer = layer; }
    std::string getSelectedSeed() const;
    std::string getSelectedTool() const;
    const std::vector<std::string>& getSeeds() const;
    const std::vector<std::string>& getTools() const;
    sf::Sprite& getSprite();
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    Inventory& getInventory();
    int& getMoney();
    void addMoney(int amount);
    void deductMoney(int amount);
};

#endif // PLAYER_H
