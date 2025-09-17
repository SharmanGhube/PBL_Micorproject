#pragma once

#include "TrafficLight.h"
#include <vector>
#include <chrono>

class TrafficSensor {
private:
    Direction direction;
    int vehicleCount;
    std::chrono::steady_clock::time_point lastDetection;
    bool isActive;
    double detectionRange;     // Detection range in meters
    
public:
    TrafficSensor(Direction dir, double range = 50.0);
    
    // Core functionality
    bool detectVehicle();
    void reset();
    void activate();
    void deactivate();
    
    // Getters
    Direction getDirection() const;
    int getVehicleCount() const;
    std::chrono::steady_clock::time_point getLastDetection() const;
    bool getActiveStatus() const;
    double getDetectionRange() const;
    std::string getDirectionString() const;
    
    // Analytics
    double getTrafficDensity() const;
    bool hasRecentActivity(int seconds = 30) const;
    void incrementCount();
};