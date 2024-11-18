#include "Player.h"
#include <cmath>
#include <iostream>
using namespace std;

Player::Player(const sf::Vector2f &startPos)
    : speed(200.0f), frameIndex(0), toolIndex(0), seedIndex(0), position(startPos)
{
    status = "down_idle";
    direction = sf::Vector2f(0, 0);

    tools = {"hoe", "axe", "water"};
    selectedTool = tools[toolIndex];

    seeds = {"corn", "tomato"};
    selectedSeed = seeds[seedIndex];

    timers["tool use"] = Timer(350, [&]()
                               { useTool(); });
    timers["tool switch"] = Timer(200, []() {}); // Empty callback
    timers["seed use"] = Timer(350, [&]()
                               { useSeed(); });
    timers["seed switch"] = Timer(200, []() {}); // Empty callback

    importAssets();
    sprite.setTexture(animations[status][frameIndex]);
    sprite.setPosition(position);
}

void Player::importAssets()
{
    std::vector<std::string> directions = {"up", "down", "left", "right",
                                           "up_idle", "down_idle", "left_idle", "right_idle",
                                           "up_hoe", "down_hoe", "left_hoe", "right_hoe",
                                           "up_axe", "down_axe", "left_axe", "right_axe",
                                           "up_water", "down_water", "left_water", "right_water"};
    for (const auto &dir : directions)
    {
        animations[dir] = importFolder("../graphics/character/" + dir);
        std::cout << "Loaded animation for: " << dir << std::endl;
    }
    if (!animations[status].empty()) {
    sprite.setTexture(animations[status][frameIndex]);
} else {
    std::cout << "Error: No frames for status " << status << std::endl;
}

}

void Player::animate(float dt)
{
    frameIndex += 57 * dt;
    if (frameIndex >= animations[status].size())
    {
        frameIndex = 0;
    }
    sprite.setTexture(animations[status][frameIndex]);
}

void Player::handleInput()
{
    if (!timers["tool use"].isActive())
    {
        direction = sf::Vector2f(0, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            direction.y = -1;
            status = "up";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            direction.y = 1;
            status = "down";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            direction.x = -1;
            status = "left";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            direction.x = 1;
            status = "right";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            timers["tool use"].activate();
            direction = sf::Vector2f(0, 0);
            frameIndex = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && !timers["tool switch"].isActive())
        {
            timers["tool switch"].activate();
            toolIndex = (toolIndex + 1) % tools.size();
            selectedTool = tools[toolIndex];
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            timers["seed use"].activate();
            direction = sf::Vector2f(0, 0);
            frameIndex = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !timers["seed switch"].isActive())
        {
            timers["seed switch"].activate();
            seedIndex = (seedIndex + 1) % seeds.size();
            selectedSeed = seeds[seedIndex];
        }
    }
}

void Player::getStatus()
{
    if (direction == sf::Vector2f(0, 0))
    {
        status = status.substr(0, status.find("_")) + "_idle";
    }
    if (timers["tool use"].isActive())
    {
        status = status.substr(0, status.find("_")) + "_" + selectedTool;
    }
}



void Player::move(float dt)
{
    if (std::sqrt(direction.x * direction.x + direction.y * direction.y) > 0)
    {
        direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
    }

    position.x += direction.x * speed * dt;
    sprite.setPosition(position.x, sprite.getPosition().y);

    position.y += direction.y * speed * dt;
    sprite.setPosition(sprite.getPosition().x, position.y);
}

void Player::updateTimers()
{
    for (auto &timer : timers)
    {
        timer.second.update();
    }
}


void Player::update(float dt)
{
    handleInput();
    getStatus();
    updateTimers();
    move(dt);
    animate(dt);
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Player::useTool()
{
    // Tool usage logic here
}

void Player::useSeed()
{
    // Seed usage logic here
}

