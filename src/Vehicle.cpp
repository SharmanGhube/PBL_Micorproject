#include "../include/Vehicle.h"
#include "../include/TrafficLight.h"
#include <chrono>

Vehicle::Vehicle(const std::string& vehicleId, VehicleType vehType, Direction dir)
    : id(vehicleId), type(vehType), direction(dir), hasPassedIntersection(false),
      arrivalTime(std::chrono::steady_clock::now()) {
    
    // Set priority based on vehicle type
    switch (type) {
        case VehicleType::AMBULANCE:
        case VehicleType::FIRE_TRUCK:
        case VehicleType::POLICE:
        case VehicleType::EMERGENCY:
            priority = 100;
            break;
        case VehicleType::BUS:
            priority = 20;
            break;
        case VehicleType::TRUCK:
            priority = 15;
            break;
        case VehicleType::CAR:
            priority = 10;
            break;
        case VehicleType::MOTORCYCLE:
            priority = 5;
            break;
        default:
            priority = 10;
            break;
    }
}

void Vehicle::setPriority(int newPriority) {
    priority = newPriority;
}

void Vehicle::markAsPassed() {
    hasPassedIntersection = true;
}

std::string Vehicle::getId() const {
    return id;
}

VehicleType Vehicle::getType() const {
    return type;
}

Direction Vehicle::getDirection() const {
    return direction;
}

int Vehicle::getPriority() const {
    return priority;
}

std::chrono::steady_clock::time_point Vehicle::getArrivalTime() const {
    return arrivalTime;
}

bool Vehicle::hasPassed() const {
    return hasPassedIntersection;
}

bool Vehicle::isEmergencyVehicle() const {
    return type == VehicleType::AMBULANCE || 
           type == VehicleType::FIRE_TRUCK || 
           type == VehicleType::POLICE || 
           type == VehicleType::EMERGENCY;
}

bool Vehicle::isCommercialVehicle() const {
    return type == VehicleType::TRUCK || type == VehicleType::BUS;
}

std::string Vehicle::getTypeString() const {
    switch (type) {
        case VehicleType::CAR: return "CAR";
        case VehicleType::TRUCK: return "TRUCK";
        case VehicleType::BUS: return "BUS";
        case VehicleType::MOTORCYCLE: return "MOTORCYCLE";
        case VehicleType::AMBULANCE: return "AMBULANCE";
        case VehicleType::FIRE_TRUCK: return "FIRE_TRUCK";
        case VehicleType::POLICE: return "POLICE";
        case VehicleType::EMERGENCY: return "EMERGENCY";
        default: return "UNKNOWN";
    }
}

std::string Vehicle::getDirectionString() const {
    switch (direction) {
        case Direction::NORTH: return "NORTH";
        case Direction::SOUTH: return "SOUTH";
        case Direction::EAST: return "EAST";
        case Direction::WEST: return "WEST";
        default: return "UNKNOWN";
    }
}

double Vehicle::getWaitTime() const {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - arrivalTime);
    return duration.count();
}

bool Vehicle::operator<(const Vehicle& other) const {
    // Higher priority vehicles should come first in priority queue
    return priority < other.priority;
}

bool Vehicle::operator>(const Vehicle& other) const {
    // For std::priority_queue with std::greater
    return priority > other.priority;
}