#pragma once

#include <string>
#include <chrono>

enum class VehicleType {
    CAR,
    TRUCK,
    BUS,
    MOTORCYCLE,
    AMBULANCE,
    FIRE_TRUCK,
    POLICE,
    EMERGENCY
};

class Vehicle {
private:
    std::string id;
    VehicleType type;
    Direction direction;
    int priority;              // Higher number = higher priority
    std::chrono::steady_clock::time_point arrivalTime;
    bool hasPassedIntersection;

public:
    Vehicle(const std::string& vehicleId, VehicleType vehType, Direction dir);
    
    // Core functionality
    void setPriority(int newPriority);
    void markAsPassed();
    
    // Getters
    std::string getId() const;
    VehicleType getType() const;
    Direction getDirection() const;
    int getPriority() const;
    std::chrono::steady_clock::time_point getArrivalTime() const;
    bool hasPassed() const;
    
    // Type checking
    bool isEmergencyVehicle() const;
    bool isCommercialVehicle() const;
    std::string getTypeString() const;
    std::string getDirectionString() const;
    
    // Wait time calculation
    double getWaitTime() const;
    
    // Comparison operators for priority queue
    bool operator<(const Vehicle& other) const;
    bool operator>(const Vehicle& other) const;
};