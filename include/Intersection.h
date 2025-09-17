#pragma once

#include "TrafficLight.h"
#include "Vehicle.h"
#include "TrafficSensor.h"
#include <vector>
#include <queue>
#include <string>
#include <map>

class Intersection {
private:
    std::string id;
    std::vector<TrafficLight> lights;
    std::vector<TrafficSensor> sensors;
    std::vector<std::queue<Vehicle>> vehicleQueues;  // One queue per direction
    bool emergencyMode;
    int cycleTime;             // Total cycle time in seconds
    int currentPhase;          // Current phase of the cycle
    std::chrono::steady_clock::time_point lastUpdate;
    
    // Timing configuration
    std::map<Direction, int> greenDuration;
    std::map<Direction, int> yellowDuration;
    int redDuration;

public:
    Intersection(const std::string& intersectionId);
    
    // Initialization
    void addTrafficLight(Direction dir);
    void addTrafficSensor(Direction dir);
    void configureTiming(Direction dir, int greenTime, int yellowTime);
    
    // Vehicle management
    void addVehicle(const Vehicle& vehicle);
    void processVehicleQueues();
    Vehicle removeVehicle(Direction dir);
    
    // Signal control
    void updateSignals();
    void handleEmergencyVehicle(Direction emergencyDir);
    void normalOperation();
    void switchToNextPhase();
    
    // Getters
    std::string getId() const;
    std::vector<TrafficLight>& getLights();
    std::vector<TrafficSensor>& getSensors();
    bool isEmergencyMode() const;
    int getCurrentPhase() const;
    
    // Queue management
    int getQueueLength(Direction dir) const;
    std::queue<Vehicle>& getQueue(Direction dir);
    
    // Analytics
    double getAverageWaitTime() const;
    int getTotalVehicleCount() const;
    void clearQueues();
    
    // Display
    void displayStatus() const;
};