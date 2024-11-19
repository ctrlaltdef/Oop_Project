#include "Timer.h"

Timer::Timer() : duration(0), active(false), callback(nullptr) {}
Timer::Timer(float duration, std::function<void()> callback)
    : duration(duration), callback(callback), active(false) {}

void Timer::activate() {
    active = true;
    clock.restart();  
}

void Timer::deactivate() {
    active = false;
}

void Timer::update() {
    if (active && clock.getElapsedTime().asMilliseconds() >= duration) {
        deactivate();
        if (callback) {
            callback();  
        }
    }
}

bool Timer::isActive() const {
    return active;
}
