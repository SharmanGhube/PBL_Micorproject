#include "../include/Intersection.h"
#include <iostream>
#include <algorithm>
#include <chrono>

Intersection::Intersection(const std::string& intersectionId)
    : id(intersectionId), emergencyMode(false), cycleTime(120), currentPhase(0),
      redDuration(2), lastUpdate(std::chrono::steady_clock::now()) {
    
    // Initialize vehicle queues for all directions
    vehicleQueues.resize(4);  // NORTH, SOUTH, EAST, WEST
    
    // Default timing configuration
    greenDuration[Direction::NORTH] = 30;
    greenDuration[Direction::SOUTH] = 30;
    greenDuration[Direction::EAST] = 25;
    greenDuration[Direction::WEST] = 25;
    
    yellowDuration[Direction::NORTH] = 5;
    yellowDuration[Direction::SOUTH] = 5;
    yellowDuration[Direction::EAST] = 5;
    yellowDuration[Direction::WEST] = 5;
}

void Intersection::addTrafficLight(Direction dir) {
    lights.emplace_back(dir, TrafficState::RED);
}

void Intersection::addTrafficSensor(Direction dir) {
    sensors.emplace_back(dir);
}

void Intersection::configureTiming(Direction dir, int greenTime, int yellowTime) {
    greenDuration[dir] = greenTime;
    yellowDuration[dir] = yellowTime;
}

void Intersection::addVehicle(const Vehicle& vehicle) {
    int dirIndex = static_cast<int>(vehicle.getDirection());
    if (dirIndex >= 0 && dirIndex < vehicleQueues.size()) {
        vehicleQueues[dirIndex].push(vehicle);
        
        // Update sensor count
        for (auto& sensor : sensors) {
            if (sensor.getDirection() == vehicle.getDirection()) {
                sensor.incrementCount();
                break;
            }
        }
    }
}

void Intersection::processVehicleQueues() {
    for (size_t i = 0; i < vehicleQueues.size(); ++i) {
        if (!vehicleQueues[i].empty()) {
            Direction dir = static_cast<Direction>(i);
            
            // Find corresponding traffic light
            auto lightIt = std::find_if(lights.begin(), lights.end(),
                [dir](const TrafficLight& light) {
                    return light.getDirection() == dir;
                });
            
            if (lightIt != lights.end() && lightIt->canProceed()) {
                // Process vehicles when light is green
                if (!vehicleQueues[i].empty()) {
                    Vehicle vehicle = vehicleQueues[i].front();
                    vehicleQueues[i].pop();
                    
                    // Mark vehicle as processed
                    vehicle.markAsPassed();
                }
            }
        }
    }
}

Vehicle Intersection::removeVehicle(Direction dir) {
    int dirIndex = static_cast<int>(dir);
    if (dirIndex >= 0 && dirIndex < vehicleQueues.size() && !vehicleQueues[dirIndex].empty()) {
        Vehicle vehicle = vehicleQueues[dirIndex].front();
        vehicleQueues[dirIndex].pop();
        return vehicle;
    }
    
    // Return dummy vehicle if queue is empty
    return Vehicle("NONE", VehicleType::CAR, dir);
}

void Intersection::updateSignals() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdate).count();
    
    if (elapsed >= 1) {  // Update every second
        // Update all traffic lights
        for (auto& light : lights) {
            light.update();
        }
        
        // Check if phase should change
        if (!emergencyMode) {
            switchToNextPhase();
        }
        
        lastUpdate = now;
    }
    
    processVehicleQueues();
}

void Intersection::handleEmergencyVehicle(Direction emergencyDir) {
    emergencyMode = true;
    
    // Set all lights to red
    for (auto& light : lights) {
        light.activateEmergency();
        light.changeState(TrafficState::RED);
    }
    
    // Set emergency direction to green
    for (auto& light : lights) {
        if (light.getDirection() == emergencyDir) {
            light.changeState(TrafficState::GREEN);
            break;
        }
    }
}

void Intersection::normalOperation() {
    emergencyMode = false;
    
    // Deactivate emergency mode for all lights
    for (auto& light : lights) {
        light.deactivateEmergency();
    }
    
    // Resume normal cycle
    currentPhase = 0;
}

void Intersection::switchToNextPhase() {
    // Simple 4-phase operation: North-South, then East-West
    static int phaseTimer = 0;
    phaseTimer++;
    
    if (phaseTimer >= 35) {  // 35 seconds per phase (30 green + 5 yellow)
        currentPhase = (currentPhase + 1) % 2;  // Toggle between 0 and 1
        phaseTimer = 0;
        
        if (currentPhase == 0) {
            // North-South Green, East-West Red
            for (auto& light : lights) {
                if (light.getDirection() == Direction::NORTH || 
                    light.getDirection() == Direction::SOUTH) {
                    light.changeState(TrafficState::GREEN);
                } else {
                    light.changeState(TrafficState::RED);
                }
            }
        } else {
            // East-West Green, North-South Red
            for (auto& light : lights) {
                if (light.getDirection() == Direction::EAST || 
                    light.getDirection() == Direction::WEST) {
                    light.changeState(TrafficState::GREEN);
                } else {
                    light.changeState(TrafficState::RED);
                }
            }
        }
    } else if (phaseTimer == 30) {
        // Change to yellow 5 seconds before phase change
        for (auto& light : lights) {
            if (light.getState() == TrafficState::GREEN) {
                light.changeState(TrafficState::YELLOW);
            }
        }
    }
}

std::string Intersection::getId() const {
    return id;
}

std::vector<TrafficLight>& Intersection::getLights() {
    return lights;
}

std::vector<TrafficSensor>& Intersection::getSensors() {
    return sensors;
}

bool Intersection::isEmergencyMode() const {
    return emergencyMode;
}

int Intersection::getCurrentPhase() const {
    return currentPhase;
}

int Intersection::getQueueLength(Direction dir) const {
    int dirIndex = static_cast<int>(dir);
    if (dirIndex >= 0 && dirIndex < vehicleQueues.size()) {
        return vehicleQueues[dirIndex].size();
    }
    return 0;
}

std::queue<Vehicle>& Intersection::getQueue(Direction dir) {
    int dirIndex = static_cast<int>(dir);
    return vehicleQueues[dirIndex];
}

double Intersection::getAverageWaitTime() const {
    double totalWaitTime = 0.0;
    int totalVehicles = 0;
    
    for (const auto& queue : vehicleQueues) {
        std::queue<Vehicle> tempQueue = queue;
        while (!tempQueue.empty()) {
            totalWaitTime += tempQueue.front().getWaitTime();
            totalVehicles++;
            tempQueue.pop();
        }
    }
    
    return totalVehicles > 0 ? totalWaitTime / totalVehicles : 0.0;
}

int Intersection::getTotalVehicleCount() const {
    int total = 0;
    for (const auto& queue : vehicleQueues) {
        total += queue.size();
    }
    return total;
}

void Intersection::clearQueues() {
    for (auto& queue : vehicleQueues) {
        while (!queue.empty()) {
            queue.pop();
        }
    }
}

void Intersection::displayStatus() const {
    std::cout << "\n=== Intersection " << id << " Status ===\n";
    std::cout << "Emergency Mode: " << (emergencyMode ? "YES" : "NO") << "\n";
    std::cout << "Current Phase: " << currentPhase << "\n";
    
    std::cout << "\nTraffic Lights:\n";
    for (const auto& light : lights) {
        std::cout << "  " << light.getDirectionString() << ": " 
                  << light.getStateString() << " (" << light.getTimeLeft() << "s)\n";
    }
    
    std::cout << "\nVehicle Queues:\n";
    const std::string directions[] = {"NORTH", "SOUTH", "EAST", "WEST"};
    for (int i = 0; i < 4; ++i) {
        std::cout << "  " << directions[i] << ": " << vehicleQueues[i].size() << " vehicles\n";
    }
    
    std::cout << "Average Wait Time: " << getAverageWaitTime() << " seconds\n";
}