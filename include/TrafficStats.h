#pragma once

#include <string>
#include <chrono>
#include <map>
#include <vector>

class TrafficStats {
private:
    int totalVehicles;
    int emergencyVehicles;
    double totalWaitTime;
    int processedVehicles;
    std::chrono::steady_clock::time_point startTime;
    
    // Per-direction statistics
    std::map<std::string, int> vehiclesByDirection;
    std::map<std::string, double> avgWaitByDirection;
    std::map<std::string, int> throughputByDirection;
    
    // Performance metrics
    double systemEfficiency;
    int totalCycles;
    int emergencyOverrides;

public:
    TrafficStats();
    
    // Update methods
    void updateVehicleCount(int count = 1);
    void updateEmergencyCount(int count = 1);
    void updateWaitTime(double waitTime);
    void updateDirectionStats(const std::string& direction, double waitTime);
    void updateSystemEfficiency(double efficiency);
    void updateCycleCount();
    void updateEmergencyOverride();
    
    // Calculation methods
    double getAverageWaitTime() const;
    double getThroughput() const;  // Vehicles per minute
    double getSystemEfficiency() const;
    int getEmergencyResponseRate() const;
    
    // Getters
    int getTotalVehicles() const;
    int getEmergencyVehicles() const;
    int getProcessedVehicles() const;
    double getTotalRunTime() const;  // Runtime in seconds
    int getTotalCycles() const;
    int getEmergencyOverrides() const;
    
    // Direction-specific getters
    int getVehiclesByDirection(const std::string& direction) const;
    double getAvgWaitByDirection(const std::string& direction) const;
    int getThroughputByDirection(const std::string& direction) const;
    
    // Report generation
    void generateReport() const;
    void saveToFile(const std::string& filename) const;
    void reset();
    
    // Display methods
    void displayRealTimeStats() const;
    void displaySummary() const;
};