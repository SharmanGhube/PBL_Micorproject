#pragma once

#include <chrono>
#include <string>

enum class TrafficState {
    RED,
    YELLOW,
    GREEN,
    FLASHING_RED,
    FLASHING_YELLOW
};

enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

class TrafficLight {
private:
    TrafficState state;
    Direction direction;
    int duration;           // Duration in seconds
    int timeLeft;          // Time remaining in current state
    bool emergencyMode;    // Emergency override
    std::chrono::steady_clock::time_point lastUpdate;

public:
    TrafficLight(Direction dir, TrafficState initialState = TrafficState::RED);
    
    // Core functionality
    void changeState(TrafficState newState);
    void update();
    void setDuration(int seconds);
    void activateEmergency();
    void deactivateEmergency();
    
    // Getters
    TrafficState getState() const;
    Direction getDirection() const;
    int getTimeLeft() const;
    bool isEmergencyActive() const;
    std::string getStateString() const;
    std::string getDirectionString() const;
    
    // State checking
    bool isRed() const;
    bool isGreen() const;
    bool isYellow() const;
    bool canProceed() const;
};