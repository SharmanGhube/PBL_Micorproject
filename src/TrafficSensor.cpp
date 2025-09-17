#include "../include/TrafficSensor.h"
#include "../include/TrafficLight.h"
#include <chrono>
#include <random>

TrafficSensor::TrafficSensor(Direction dir, double range)
    : direction(dir), vehicleCount(0), isActive(true), detectionRange(range),
      lastDetection(std::chrono::steady_clock::now()) {
}

bool TrafficSensor::detectVehicle() {
    if (!isActive) {
        return false;
    }
    
    // Simulate vehicle detection with some randomness
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 100);
    
    // 30% chance of detecting a vehicle each check
    bool detected = dis(gen) <= 30;
    
    if (detected) {
        vehicleCount++;
        lastDetection = std::chrono::steady_clock::now();
    }
    
    return detected;
}

void TrafficSensor::reset() {
    vehicleCount = 0;
    lastDetection = std::chrono::steady_clock::now();
}

void TrafficSensor::activate() {
    isActive = true;
}

void TrafficSensor::deactivate() {
    isActive = false;
}

Direction TrafficSensor::getDirection() const {
    return direction;
}

int TrafficSensor::getVehicleCount() const {
    return vehicleCount;
}

std::chrono::steady_clock::time_point TrafficSensor::getLastDetection() const {
    return lastDetection;
}

bool TrafficSensor::getActiveStatus() const {
    return isActive;
}

double TrafficSensor::getDetectionRange() const {
    return detectionRange;
}

std::string TrafficSensor::getDirectionString() const {
    switch (direction) {
        case Direction::NORTH: return "NORTH";
        case Direction::SOUTH: return "SOUTH";
        case Direction::EAST: return "EAST";
        case Direction::WEST: return "WEST";
        default: return "UNKNOWN";
    }
}

double TrafficSensor::getTrafficDensity() const {
    // Calculate vehicles per minute based on recent detections
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(now - lastDetection);
    
    if (duration.count() == 0) {
        return vehicleCount;  // Recent activity
    }
    
    return static_cast<double>(vehicleCount) / duration.count();
}

bool TrafficSensor::hasRecentActivity(int seconds) const {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastDetection);
    return duration.count() <= seconds;
}

void TrafficSensor::incrementCount() {
    vehicleCount++;
    lastDetection = std::chrono::steady_clock::now();
}