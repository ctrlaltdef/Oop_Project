#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include "Timer.h"
#include "Settings.h"
#include "Support.h"

class Player {
private:
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

public:
    Player(const sf::Vector2f& startPos);
    void handleInput();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    std::string getSelectedSeed() const {
    return selectedSeed;
    }
    std::string getSelectedTool() const{
        return selectedTool;
    }
    const std::vector<std::string>& getSeeds() const{
        return seeds;
    }
    const std::vector<std::string>& getTools() const{
        return tools;
    }
    sf::Sprite& getSprite(){
        return sprite;
    }
  

};

#endif // PLAYER_H