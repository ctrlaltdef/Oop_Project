#ifndef TIMER_H
#define TIMER_H

#include <SFML/System.hpp>
#include <functional>

class Timer {
private:
    sf::Clock clock;   
    float duration;    
    bool active;       
    std::function<void()> callback;  
public:
    Timer();
    Timer(float duration, std::function<void()> callback = nullptr);
    void activate();
    void deactivate();
    void update();
    bool isActive() const;
};

#endif
