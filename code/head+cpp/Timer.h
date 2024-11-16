#ifndef TIMER_H
#define TIMER_H

#include <SFML/System.hpp>
#include <functional>

class Timer {
private:
    sf::Clock clock;   // For time tracking
    float duration;    // Duration for timer
    bool active;       // Active state of the timer
    std::function<void()> callback;  // Callback function when timer ends

public:
    Timer();
    Timer(float duration, std::function<void()> callback = nullptr);
    void activate();
    void deactivate();
    void update();
    bool isActive() const;
};

#endif
