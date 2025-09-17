#include "../include/TrafficLight.h"
#include <iostream>

TrafficLight::TrafficLight(Direction dir, TrafficState initialState)
    : direction(dir), state(initialState), duration(30), timeLeft(30), 
      emergencyMode(false), lastUpdate(std::chrono::steady_clock::now()) {
}

void TrafficLight::changeState(TrafficState newState) {
    state = newState;
    
    // Set default durations based on state
    switch (state) {
        case TrafficState::RED:
            duration = 30;
            break;
        case TrafficState::YELLOW:
            duration = 5;
            break;
        case TrafficState::GREEN:
            duration = 25;
            break;
        case TrafficState::FLASHING_RED:
        case TrafficState::FLASHING_YELLOW:
            duration = 1;  // Flashing cycle
            break;
    }
    
    timeLeft = duration;
    lastUpdate = std::chrono::steady_clock::now();
}

void TrafficLight::update() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate).count();
    
    if (elapsed >= 1) {  // Update every second
        if (timeLeft > 0) {
            timeLeft--;
        }
        lastUpdate = now;
    }
}

void TrafficLight::setDuration(int seconds) {
    duration = seconds;
    timeLeft = seconds;
}

void TrafficLight::activateEmergency() {
    emergencyMode = true;
    changeState(TrafficState::RED);  // Default emergency state
}

void TrafficLight::deactivateEmergency() {
    emergencyMode = false;
}

TrafficState TrafficLight::getState() const {
    return state;
}

Direction TrafficLight::getDirection() const {
    return direction;
}

int TrafficLight::getTimeLeft() const {
    return timeLeft;
}

bool TrafficLight::isEmergencyActive() const {
    return emergencyMode;
}

std::string TrafficLight::getStateString() const {
    switch (state) {
        case TrafficState::RED: return "RED";
        case TrafficState::YELLOW: return "YELLOW";
        case TrafficState::GREEN: return "GREEN";
        case TrafficState::FLASHING_RED: return "FLASHING_RED";
        case TrafficState::FLASHING_YELLOW: return "FLASHING_YELLOW";
        default: return "UNKNOWN";
    }
}

std::string TrafficLight::getDirectionString() const {
    switch (direction) {
        case Direction::NORTH: return "NORTH";
        case Direction::SOUTH: return "SOUTH";
        case Direction::EAST: return "EAST";
        case Direction::WEST: return "WEST";
        default: return "UNKNOWN";
    }
}

bool TrafficLight::isRed() const {
    return state == TrafficState::RED || state == TrafficState::FLASHING_RED;
}

bool TrafficLight::isGreen() const {
    return state == TrafficState::GREEN;
}

bool TrafficLight::isYellow() const {
    return state == TrafficState::YELLOW || state == TrafficState::FLASHING_YELLOW;
}

bool TrafficLight::canProceed() const {
    return state == TrafficState::GREEN;
}