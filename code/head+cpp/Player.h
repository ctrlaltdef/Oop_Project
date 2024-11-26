#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include "Timer.h"
#include "Settings.h"
#include "Support.h"
#include "SoilLayer.h"
#include "Inventory.h"
#include "Market.h"

class Player {
private:
    SoilLayer* soilLayer;
    sf::Vector2f targetPosition;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f direction;
    sf::Vector2f position;
    float speed;
    std::map<std::string, std::vector<sf::Texture>> animations;
    std::string status;
    int frameIndex;

    std::map<std::string, Timer> timers;
    std::vector<std::string> tools;
    int toolIndex;
    std::string selectedTool;

    std::vector<std::string> seeds;
    int seedIndex;
    std::string selectedSeed;

    void importAssets();
    void animate(float dt);
    void move(float dt);
    void updateTimers();
    void getStatus();
    void useTool();
    void useSeed();

    Inventory inventory; 
    int money;           

public:
    void setSoilLayer(SoilLayer* layer) { soilLayer = layer; }
    Player(const sf::Vector2f& startPos);
    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);

    std::string getSelectedSeed() const;
    std::string getSelectedTool() const;
    const std::vector<std::string>& getSeeds() const;
    const std::vector<std::string>& getTools() const;
    sf::Sprite& getSprite();  
    sf::Vector2f getPosition() const ;
    void setPosition(const sf::Vector2f& position) ;

    void interactWithMarket(); // Interaction with the market
    Inventory& getInventory(); 
    int getMoney() const;
    void addMoney(int amount);
    bool deductMoney(int amount);

};

#endif // PLAYER_H
