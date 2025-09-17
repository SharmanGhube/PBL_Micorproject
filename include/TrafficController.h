#pragma once

#include "Intersection.h"
#include "TrafficStats.h"
#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <memory>

class TrafficController {
private:
    std::vector<std::unique_ptr<Intersection>> intersections;
    std::priority_queue<Vehicle, std::vector<Vehicle>, std::greater<Vehicle>> emergencyQueue;
    TrafficStats statistics;
    std::atomic<bool> running;
    std::atomic<bool> emergencyActive;
    
    // System configuration
    int simulationSpeed;       // Simulation speed multiplier
    bool realTimeMode;         // Real-time vs accelerated simulation
    std::chrono::steady_clock::time_point systemStartTime;
    
    // Threading
    std::thread controllerThread;
    std::thread simulationThread;

public:
    TrafficController();
    ~TrafficController();
    
    // Intersection management
    void addIntersection(const std::string& id);
    Intersection* getIntersection(const std::string& id);
    void removeIntersection(const std::string& id);
    
    // Emergency handling
    void handleEmergencyVehicle(const Vehicle& emergency);
    void processEmergencyQueue();
    void clearEmergencyMode();
    
    // Traffic optimization
    void optimizeTrafficFlow();
    void adaptiveSignalTiming();
    void balanceIntersectionLoad();
    
    // System control
    void start();
    void stop();
    void pause();
    void resume();
    bool isRunning() const;
    
    // Configuration
    void setSimulationSpeed(int speed);
    void setRealTimeMode(bool realTime);
    void configureIntersection(const std::string& id, Direction dir, int greenTime, int yellowTime);
    
    // Simulation
    void generateRandomTraffic();
    void simulateVehicleFlow();
    void updateAllIntersections();
    
    // Statistics and reporting
    TrafficStats& getStatistics();
    void generateSystemReport() const;
    void saveReportToFile(const std::string& filename) const;
    void displaySystemStatus() const;
    
    // Utility methods
    void reset();
    int getIntersectionCount() const;
    std::vector<std::string> getIntersectionIds() const;
    
private:
    // Internal helper methods
    void controllerLoop();
    void simulationLoop();
    void processIntersection(Intersection& intersection);
    void checkEmergencyConditions();
    Direction getRandomDirection();
    VehicleType getRandomVehicleType();
};