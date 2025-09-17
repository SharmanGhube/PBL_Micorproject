#include "../include/TrafficController.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>

TrafficController::TrafficController()
    : running(false), emergencyActive(false), simulationSpeed(1), 
      realTimeMode(true), systemStartTime(std::chrono::steady_clock::now()) {
}

TrafficController::~TrafficController() {
    stop();
}

void TrafficController::addIntersection(const std::string& id) {
    auto intersection = std::make_unique<Intersection>(id);
    
    // Add traffic lights for all directions
    intersection->addTrafficLight(Direction::NORTH);
    intersection->addTrafficLight(Direction::SOUTH);
    intersection->addTrafficLight(Direction::EAST);
    intersection->addTrafficLight(Direction::WEST);
    
    // Add sensors for all directions
    intersection->addTrafficSensor(Direction::NORTH);
    intersection->addTrafficSensor(Direction::SOUTH);
    intersection->addTrafficSensor(Direction::EAST);
    intersection->addTrafficSensor(Direction::WEST);
    
    intersections.push_back(std::move(intersection));
    
    std::cout << "Added intersection: " << id << "\n";
}

Intersection* TrafficController::getIntersection(const std::string& id) {
    auto it = std::find_if(intersections.begin(), intersections.end(),
        [&id](const std::unique_ptr<Intersection>& intersection) {
            return intersection->getId() == id;
        });
    
    return (it != intersections.end()) ? it->get() : nullptr;
}

void TrafficController::removeIntersection(const std::string& id) {
    intersections.erase(
        std::remove_if(intersections.begin(), intersections.end(),
            [&id](const std::unique_ptr<Intersection>& intersection) {
                return intersection->getId() == id;
            }),
        intersections.end());
}

void TrafficController::handleEmergencyVehicle(const Vehicle& emergency) {
    if (emergency.isEmergencyVehicle()) {
        emergencyQueue.push(emergency);
        emergencyActive = true;
        
        // Find intersection and activate emergency mode
        // For simplicity, use first intersection
        if (!intersections.empty()) {
            intersections[0]->handleEmergencyVehicle(emergency.getDirection());
        }
        
        statistics.updateEmergencyCount();
        statistics.updateEmergencyOverride();
        
        std::cout << "Emergency vehicle detected: " << emergency.getTypeString() 
                  << " heading " << emergency.getDirectionString() << "\n";
    }
}

void TrafficController::processEmergencyQueue() {
    while (!emergencyQueue.empty() && emergencyActive) {
        Vehicle emergency = emergencyQueue.top();
        emergencyQueue.pop();
        
        // Process emergency vehicle through intersection
        for (auto& intersection : intersections) {
            intersection->addVehicle(emergency);
        }
        
        if (emergencyQueue.empty()) {
            clearEmergencyMode();
        }
    }
}

void TrafficController::clearEmergencyMode() {
    emergencyActive = false;
    
    // Return all intersections to normal operation
    for (auto& intersection : intersections) {
        intersection->normalOperation();
    }
    
    std::cout << "Emergency mode cleared. Returning to normal operation.\n";
}

void TrafficController::optimizeTrafficFlow() {
    // Implement adaptive traffic control
    for (auto& intersection : intersections) {
        // Analyze queue lengths
        std::vector<int> queueLengths(4);
        queueLengths[0] = intersection->getQueueLength(Direction::NORTH);
        queueLengths[1] = intersection->getQueueLength(Direction::SOUTH);
        queueLengths[2] = intersection->getQueueLength(Direction::EAST);
        queueLengths[3] = intersection->getQueueLength(Direction::WEST);
        
        // Find direction with longest queue
        auto maxIt = std::max_element(queueLengths.begin(), queueLengths.end());
        int maxIndex = std::distance(queueLengths.begin(), maxIt);
        Direction priorityDirection = static_cast<Direction>(maxIndex);
        
        // Adjust timing if significant difference
        if (*maxIt > 5) {  // If queue has more than 5 vehicles
            intersection->configureTiming(priorityDirection, 35, 5);  // Extend green time
        }
    }
}

void TrafficController::adaptiveSignalTiming() {
    // Implement time-of-day adjustments
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto tm = *std::localtime(&time_t);
    
    int hour = tm.tm_hour;
    
    // Rush hour adjustments (7-9 AM, 5-7 PM)
    if ((hour >= 7 && hour <= 9) || (hour >= 17 && hour <= 19)) {
        for (auto& intersection : intersections) {
            // Increase main road green time during rush hours
            intersection->configureTiming(Direction::NORTH, 40, 5);
            intersection->configureTiming(Direction::SOUTH, 40, 5);
        }
    }
}

void TrafficController::balanceIntersectionLoad() {
    // Simple load balancing between intersections
    if (intersections.size() > 1) {
        int totalVehicles = 0;
        for (const auto& intersection : intersections) {
            totalVehicles += intersection->getTotalVehicleCount();
        }
        
        int avgLoad = totalVehicles / intersections.size();
        
        // Adjust timing for heavily loaded intersections
        for (auto& intersection : intersections) {
            if (intersection->getTotalVehicleCount() > avgLoad + 3) {
                // Reduce cycle time for overloaded intersections
                intersection->configureTiming(Direction::NORTH, 25, 4);
                intersection->configureTiming(Direction::SOUTH, 25, 4);
                intersection->configureTiming(Direction::EAST, 20, 4);
                intersection->configureTiming(Direction::WEST, 20, 4);
            }
        }
    }
}

void TrafficController::start() {
    if (running) {
        std::cout << "Traffic controller is already running.\n";
        return;
    }
    
    running = true;
    systemStartTime = std::chrono::steady_clock::now();
    
    std::cout << "Starting traffic management system...\n";
    
    // Start control threads
    controllerThread = std::thread(&TrafficController::controllerLoop, this);
    simulationThread = std::thread(&TrafficController::simulationLoop, this);
    
    std::cout << "Traffic controller started successfully.\n";
}

void TrafficController::stop() {
    if (!running) {
        return;
    }
    
    running = false;
    
    // Wait for threads to finish
    if (controllerThread.joinable()) {
        controllerThread.join();
    }
    if (simulationThread.joinable()) {
        simulationThread.join();
    }
    
    std::cout << "Traffic controller stopped.\n";
}

void TrafficController::pause() {
    // Implementation for pause functionality
    std::cout << "System paused.\n";
}

void TrafficController::resume() {
    // Implementation for resume functionality
    std::cout << "System resumed.\n";
}

bool TrafficController::isRunning() const {
    return running;
}

void TrafficController::setSimulationSpeed(int speed) {
    simulationSpeed = speed;
}

void TrafficController::setRealTimeMode(bool realTime) {
    realTimeMode = realTime;
}

void TrafficController::configureIntersection(const std::string& id, Direction dir, int greenTime, int yellowTime) {
    Intersection* intersection = getIntersection(id);
    if (intersection) {
        intersection->configureTiming(dir, greenTime, yellowTime);
    }
}

void TrafficController::generateRandomTraffic() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dirDis(0, 3);
    static std::uniform_int_distribution<> typeDis(0, 7);
    static std::uniform_int_distribution<> emergencyDis(1, 100);
    static int vehicleCounter = 0;
    
    // Generate vehicle every few seconds
    Direction dir = static_cast<Direction>(dirDis(gen));
    VehicleType type = static_cast<VehicleType>(typeDis(gen));
    
    // 5% chance for emergency vehicle
    if (emergencyDis(gen) <= 5) {
        type = VehicleType::AMBULANCE;
    }
    
    std::string id = "V" + std::to_string(++vehicleCounter);
    Vehicle newVehicle(id, type, dir);
    
    // Add to first intersection (expand for multiple intersections)
    if (!intersections.empty()) {
        intersections[0]->addVehicle(newVehicle);
        statistics.updateVehicleCount();
        
        if (newVehicle.isEmergencyVehicle()) {
            handleEmergencyVehicle(newVehicle);
        }
    }
}

void TrafficController::simulateVehicleFlow() {
    generateRandomTraffic();
    optimizeTrafficFlow();
    adaptiveSignalTiming();
    balanceIntersectionLoad();
}

void TrafficController::updateAllIntersections() {
    for (auto& intersection : intersections) {
        intersection->updateSignals();
    }
    
    statistics.updateCycleCount();
}

TrafficStats& TrafficController::getStatistics() {
    return statistics;
}

void TrafficController::generateSystemReport() const {
    statistics.generateReport();
}

void TrafficController::saveReportToFile(const std::string& filename) const {
    statistics.saveToFile(filename);
}

void TrafficController::displaySystemStatus() const {
    std::cout << "\n=== SYSTEM STATUS ===\n";
    std::cout << "Running: " << (running ? "YES" : "NO") << "\n";
    std::cout << "Emergency Mode: " << (emergencyActive ? "ACTIVE" : "NORMAL") << "\n";
    std::cout << "Intersections: " << intersections.size() << "\n";
    std::cout << "Simulation Speed: " << simulationSpeed << "x\n";
    std::cout << "Real-time Mode: " << (realTimeMode ? "YES" : "NO") << "\n";
    
    // Display each intersection status
    for (const auto& intersection : intersections) {
        intersection->displayStatus();
    }
    
    statistics.displaySummary();
}

void TrafficController::reset() {
    stop();
    
    // Clear all intersections
    intersections.clear();
    
    // Clear emergency queue
    while (!emergencyQueue.empty()) {
        emergencyQueue.pop();
    }
    
    // Reset statistics
    statistics.reset();
    
    emergencyActive = false;
    
    std::cout << "Traffic controller reset.\n";
}

int TrafficController::getIntersectionCount() const {
    return intersections.size();
}

std::vector<std::string> TrafficController::getIntersectionIds() const {
    std::vector<std::string> ids;
    for (const auto& intersection : intersections) {
        ids.push_back(intersection->getId());
    }
    return ids;
}

void TrafficController::controllerLoop() {
    while (running) {
        updateAllIntersections();
        processEmergencyQueue();
        
        // Update system efficiency
        double efficiency = 85.0;  // Simplified efficiency calculation
        statistics.updateSystemEfficiency(efficiency);
        
        // Sleep based on simulation speed
        int sleepTime = realTimeMode ? 1000 / simulationSpeed : 100;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
}

void TrafficController::simulationLoop() {
    while (running) {
        simulateVehicleFlow();
        
        // Sleep for traffic generation interval
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

void TrafficController::processIntersection(Intersection& intersection) {
    intersection.updateSignals();
    
    // Calculate wait times for statistics
    double avgWait = intersection.getAverageWaitTime();
    if (avgWait > 0) {
        statistics.updateWaitTime(avgWait);
    }
}

void TrafficController::checkEmergencyConditions() {
    // Check for emergency vehicles in queues
    for (auto& intersection : intersections) {
        for (int i = 0; i < 4; ++i) {
            Direction dir = static_cast<Direction>(i);
            auto& queue = intersection->getQueue(dir);
            
            if (!queue.empty() && queue.front().isEmergencyVehicle()) {
                handleEmergencyVehicle(queue.front());
            }
        }
    }
}

Direction TrafficController::getRandomDirection() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 3);
    return static_cast<Direction>(dis(gen));
}

VehicleType TrafficController::getRandomVehicleType() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 7);
    return static_cast<VehicleType>(dis(gen));
}