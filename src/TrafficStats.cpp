#include "../include/TrafficStats.h"
#include <iostream>
#include <fstream>
#include <iomanip>

TrafficStats::TrafficStats()
    : totalVehicles(0), emergencyVehicles(0), totalWaitTime(0.0), 
      processedVehicles(0), systemEfficiency(0.0), totalCycles(0), 
      emergencyOverrides(0), startTime(std::chrono::steady_clock::now()) {
}

void TrafficStats::updateVehicleCount(int count) {
    totalVehicles += count;
}

void TrafficStats::updateEmergencyCount(int count) {
    emergencyVehicles += count;
}

void TrafficStats::updateWaitTime(double waitTime) {
    totalWaitTime += waitTime;
    processedVehicles++;
}

void TrafficStats::updateDirectionStats(const std::string& direction, double waitTime) {
    vehiclesByDirection[direction]++;
    
    // Update average wait time for this direction
    double currentAvg = avgWaitByDirection[direction];
    int count = vehiclesByDirection[direction];
    avgWaitByDirection[direction] = ((currentAvg * (count - 1)) + waitTime) / count;
    
    throughputByDirection[direction]++;
}

void TrafficStats::updateSystemEfficiency(double efficiency) {
    systemEfficiency = efficiency;
}

void TrafficStats::updateCycleCount() {
    totalCycles++;
}

void TrafficStats::updateEmergencyOverride() {
    emergencyOverrides++;
}

double TrafficStats::getAverageWaitTime() const {
    return processedVehicles > 0 ? totalWaitTime / processedVehicles : 0.0;
}

double TrafficStats::getThroughput() const {
    double runtimeMinutes = getTotalRunTime() / 60.0;
    return runtimeMinutes > 0 ? processedVehicles / runtimeMinutes : 0.0;
}

double TrafficStats::getSystemEfficiency() const {
    return systemEfficiency;
}

int TrafficStats::getEmergencyResponseRate() const {
    return totalVehicles > 0 ? (emergencyVehicles * 100) / totalVehicles : 0;
}

int TrafficStats::getTotalVehicles() const {
    return totalVehicles;
}

int TrafficStats::getEmergencyVehicles() const {
    return emergencyVehicles;
}

int TrafficStats::getProcessedVehicles() const {
    return processedVehicles;
}

double TrafficStats::getTotalRunTime() const {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
    return duration.count();
}

int TrafficStats::getTotalCycles() const {
    return totalCycles;
}

int TrafficStats::getEmergencyOverrides() const {
    return emergencyOverrides;
}

int TrafficStats::getVehiclesByDirection(const std::string& direction) const {
    auto it = vehiclesByDirection.find(direction);
    return it != vehiclesByDirection.end() ? it->second : 0;
}

double TrafficStats::getAvgWaitByDirection(const std::string& direction) const {
    auto it = avgWaitByDirection.find(direction);
    return it != avgWaitByDirection.end() ? it->second : 0.0;
}

int TrafficStats::getThroughputByDirection(const std::string& direction) const {
    auto it = throughputByDirection.find(direction);
    return it != throughputByDirection.end() ? it->second : 0;
}

void TrafficStats::generateReport() const {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "         TRAFFIC MANAGEMENT SYSTEM REPORT\n";
    std::cout << std::string(50, '=') << "\n";
    
    std::cout << std::fixed << std::setprecision(2);
    
    // Overall statistics
    std::cout << "\nOVERALL STATISTICS:\n";
    std::cout << "  Total Runtime: " << getTotalRunTime() << " seconds\n";
    std::cout << "  Total Vehicles Processed: " << totalVehicles << "\n";
    std::cout << "  Emergency Vehicles: " << emergencyVehicles << "\n";
    std::cout << "  Average Wait Time: " << getAverageWaitTime() << " seconds\n";
    std::cout << "  System Throughput: " << getThroughput() << " vehicles/minute\n";
    std::cout << "  System Efficiency: " << systemEfficiency << "%\n";
    std::cout << "  Total Signal Cycles: " << totalCycles << "\n";
    std::cout << "  Emergency Overrides: " << emergencyOverrides << "\n";
    
    // Direction-wise statistics
    std::cout << "\nDIRECTION-WISE STATISTICS:\n";
    const std::string directions[] = {"NORTH", "SOUTH", "EAST", "WEST"};
    
    for (const auto& dir : directions) {
        int vehicles = getVehiclesByDirection(dir);
        if (vehicles > 0) {
            std::cout << "  " << dir << ":\n";
            std::cout << "    Vehicles: " << vehicles << "\n";
            std::cout << "    Avg Wait: " << getAvgWaitByDirection(dir) << " seconds\n";
            std::cout << "    Throughput: " << getThroughputByDirection(dir) << " vehicles\n";
        }
    }
    
    // Performance metrics
    std::cout << "\nPERFORMANCE METRICS:\n";
    std::cout << "  Emergency Response Rate: " << getEmergencyResponseRate() << "%\n";
    std::cout << "  Cycle Efficiency: " << (totalCycles > 0 ? (double)processedVehicles / totalCycles : 0) << " vehicles/cycle\n";
    std::cout << "  Average Cycle Time: " << (totalCycles > 0 ? getTotalRunTime() / totalCycles : 0) << " seconds\n";
    
    std::cout << std::string(50, '=') << "\n";
}

void TrafficStats::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }
    
    file << "Traffic Management System Report\n";
    file << "Generated on: " << std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count() << "\n\n";
    
    file << "Overall Statistics:\n";
    file << "Total Runtime: " << getTotalRunTime() << " seconds\n";
    file << "Total Vehicles: " << totalVehicles << "\n";
    file << "Emergency Vehicles: " << emergencyVehicles << "\n";
    file << "Average Wait Time: " << getAverageWaitTime() << " seconds\n";
    file << "Throughput: " << getThroughput() << " vehicles/minute\n";
    file << "System Efficiency: " << systemEfficiency << "%\n";
    file << "Total Cycles: " << totalCycles << "\n";
    file << "Emergency Overrides: " << emergencyOverrides << "\n\n";
    
    file << "Direction Statistics:\n";
    for (const auto& pair : vehiclesByDirection) {
        file << pair.first << ": " << pair.second << " vehicles, ";
        file << "Avg Wait: " << getAvgWaitByDirection(pair.first) << " seconds\n";
    }
    
    file.close();
    std::cout << "Report saved to " << filename << "\n";
}

void TrafficStats::reset() {
    totalVehicles = 0;
    emergencyVehicles = 0;
    totalWaitTime = 0.0;
    processedVehicles = 0;
    systemEfficiency = 0.0;
    totalCycles = 0;
    emergencyOverrides = 0;
    
    vehiclesByDirection.clear();
    avgWaitByDirection.clear();
    throughputByDirection.clear();
    
    startTime = std::chrono::steady_clock::now();
}

void TrafficStats::displayRealTimeStats() const {
    std::cout << "\r";  // Carriage return to overwrite previous line
    std::cout << "Runtime: " << std::setw(4) << (int)getTotalRunTime() << "s | ";
    std::cout << "Vehicles: " << std::setw(4) << totalVehicles << " | ";
    std::cout << "Avg Wait: " << std::setw(5) << std::setprecision(1) << getAverageWaitTime() << "s | ";
    std::cout << "Throughput: " << std::setw(5) << std::setprecision(1) << getThroughput() << " v/m";
    std::cout.flush();
}

void TrafficStats::displaySummary() const {
    std::cout << "\n=== TRAFFIC SYSTEM SUMMARY ===\n";
    std::cout << "Total Vehicles: " << totalVehicles << "\n";
    std::cout << "Emergency Vehicles: " << emergencyVehicles << "\n";
    std::cout << "Average Wait Time: " << std::setprecision(2) << getAverageWaitTime() << " seconds\n";
    std::cout << "System Throughput: " << std::setprecision(2) << getThroughput() << " vehicles/minute\n";
    std::cout << "Runtime: " << getTotalRunTime() << " seconds\n";
}