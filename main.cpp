#include "include/TrafficController.h"
#include "include/TrafficLight.h"
#include "include/Vehicle.h"
#include "include/Intersection.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class TrafficManagementDemo {
private:
    TrafficController controller;
    bool demoRunning;

public:
    TrafficManagementDemo() : demoRunning(false) {}

    void displayMainMenu() {
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "        SMART TRAFFIC MANAGEMENT SYSTEM\n";
        std::cout << std::string(60, '=') << "\n";
        std::cout << "1. Start Traffic System\n";
        std::cout << "2. Add Intersection\n";
        std::cout << "3. Add Vehicle\n";
        std::cout << "4. Add Emergency Vehicle\n";
        std::cout << "5. Display System Status\n";
        std::cout << "6. Generate Report\n";
        std::cout << "7. Run Demo Simulation\n";
        std::cout << "8. Configure Intersection\n";
        std::cout << "9. Stop System\n";
        std::cout << "0. Exit\n";
        std::cout << std::string(60, '-') << "\n";
        std::cout << "Enter your choice: ";
    }

    void startSystem() {
        if (controller.isRunning()) {
            std::cout << "System is already running!\n";
            return;
        }
        
        // Add default intersection if none exists
        if (controller.getIntersectionCount() == 0) {
            controller.addIntersection("Main_Street_Intersection");
        }
        
        controller.start();
        demoRunning = true;
        std::cout << "Traffic management system started successfully!\n";
    }

    void stopSystem() {
        controller.stop();
        demoRunning = false;
        std::cout << "Traffic management system stopped.\n";
    }

    void addIntersection() {
        std::string id;
        std::cout << "Enter intersection ID: ";
        std::cin.ignore();
        std::getline(std::cin, id);
        
        controller.addIntersection(id);
    }

    void addVehicle() {
        if (!controller.isRunning()) {
            std::cout << "Please start the system first!\n";
            return;
        }

        std::string id;
        int typeChoice, dirChoice;
        
        std::cout << "Enter vehicle ID: ";
        std::cin.ignore();
        std::getline(std::cin, id);
        
        std::cout << "Select vehicle type:\n";
        std::cout << "0. Car  1. Truck  2. Bus  3. Motorcycle\n";
        std::cout << "4. Ambulance  5. Fire Truck  6. Police  7. Emergency\n";
        std::cout << "Choice: ";
        std::cin >> typeChoice;
        
        std::cout << "Select direction:\n";
        std::cout << "0. North  1. South  2. East  3. West\n";
        std::cout << "Choice: ";
        std::cin >> dirChoice;
        
        if (typeChoice >= 0 && typeChoice <= 7 && dirChoice >= 0 && dirChoice <= 3) {
            VehicleType type = static_cast<VehicleType>(typeChoice);
            Direction dir = static_cast<Direction>(dirChoice);
            
            Vehicle vehicle(id, type, dir);
            
            // Add to first intersection
            auto intersectionIds = controller.getIntersectionIds();
            if (!intersectionIds.empty()) {
                Intersection* intersection = controller.getIntersection(intersectionIds[0]);
                if (intersection) {
                    intersection->addVehicle(vehicle);
                    controller.getStatistics().updateVehicleCount();
                    
                    if (vehicle.isEmergencyVehicle()) {
                        controller.handleEmergencyVehicle(vehicle);
                    }
                    
                    std::cout << "Vehicle " << id << " added successfully!\n";
                }
            } else {
                std::cout << "No intersections available. Please add an intersection first.\n";
            }
        } else {
            std::cout << "Invalid choice!\n";
        }
    }

    void addEmergencyVehicle() {
        if (!controller.isRunning()) {
            std::cout << "Please start the system first!\n";
            return;
        }

        std::string id;
        int dirChoice;
        
        std::cout << "Enter emergency vehicle ID: ";
        std::cin.ignore();
        std::getline(std::cin, id);
        
        std::cout << "Select direction:\n";
        std::cout << "0. North  1. South  2. East  3. West\n";
        std::cout << "Choice: ";
        std::cin >> dirChoice;
        
        if (dirChoice >= 0 && dirChoice <= 3) {
            Direction dir = static_cast<Direction>(dirChoice);
            Vehicle emergency(id, VehicleType::AMBULANCE, dir);
            
            controller.handleEmergencyVehicle(emergency);
            
            // Also add to intersection
            auto intersectionIds = controller.getIntersectionIds();
            if (!intersectionIds.empty()) {
                Intersection* intersection = controller.getIntersection(intersectionIds[0]);
                if (intersection) {
                    intersection->addVehicle(emergency);
                }
            }
            
            std::cout << "Emergency vehicle " << id << " added and prioritized!\n";
        } else {
            std::cout << "Invalid direction!\n";
        }
    }

    void displayStatus() {
        controller.displaySystemStatus();
    }

    void generateReport() {
        controller.generateSystemReport();
        
        std::cout << "\nWould you like to save the report to a file? (y/n): ";
        char choice;
        std::cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin.ignore();
            std::getline(std::cin, filename);
            controller.saveReportToFile(filename);
        }
    }

    void runDemoSimulation() {
        std::cout << "Starting demo simulation...\n";
        std::cout << "This will run for 30 seconds with automatic traffic generation.\n";
        std::cout << "Press Enter to start...";
        std::cin.ignore();
        std::cin.get();
        
        // Ensure system is running
        if (!controller.isRunning()) {
            startSystem();
        }
        
        // Run simulation for 30 seconds
        auto startTime = std::chrono::steady_clock::now();
        auto endTime = startTime + std::chrono::seconds(30);
        
        std::cout << "Demo simulation running...\n";
        
        int vehicleCounter = 1;
        while (std::chrono::steady_clock::now() < endTime) {
            // Add random vehicles
            if (vehicleCounter % 3 == 0) {  // Add vehicle every 3rd iteration
                Direction dir = static_cast<Direction>(rand() % 4);
                VehicleType type = static_cast<VehicleType>(rand() % 8);
                
                std::string id = "DEMO_V" + std::to_string(vehicleCounter);
                Vehicle vehicle(id, type, dir);
                
                auto intersectionIds = controller.getIntersectionIds();
                if (!intersectionIds.empty()) {
                    Intersection* intersection = controller.getIntersection(intersectionIds[0]);
                    if (intersection) {
                        intersection->addVehicle(vehicle);
                        controller.getStatistics().updateVehicleCount();
                        
                        if (vehicle.isEmergencyVehicle()) {
                            controller.handleEmergencyVehicle(vehicle);
                        }
                    }
                }
            }
            
            // Display real-time stats
            controller.getStatistics().displayRealTimeStats();
            
            vehicleCounter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        
        std::cout << "\nDemo simulation completed!\n";
        generateReport();
    }

    void configureIntersection() {
        if (controller.getIntersectionCount() == 0) {
            std::cout << "No intersections available. Please add an intersection first.\n";
            return;
        }
        
        std::cout << "Available intersections:\n";
        auto ids = controller.getIntersectionIds();
        for (size_t i = 0; i < ids.size(); ++i) {
            std::cout << i + 1 << ". " << ids[i] << "\n";
        }
        
        int choice;
        std::cout << "Select intersection: ";
        std::cin >> choice;
        
        if (choice > 0 && choice <= (int)ids.size()) {
            std::string intersectionId = ids[choice - 1];
            
            std::cout << "Select direction to configure:\n";
            std::cout << "0. North  1. South  2. East  3. West\n";
            std::cout << "Choice: ";
            int dirChoice;
            std::cin >> dirChoice;
            
            if (dirChoice >= 0 && dirChoice <= 3) {
                Direction dir = static_cast<Direction>(dirChoice);
                
                int greenTime, yellowTime;
                std::cout << "Enter green light duration (seconds): ";
                std::cin >> greenTime;
                std::cout << "Enter yellow light duration (seconds): ";
                std::cin >> yellowTime;
                
                controller.configureIntersection(intersectionId, dir, greenTime, yellowTime);
                std::cout << "Intersection configured successfully!\n";
            } else {
                std::cout << "Invalid direction!\n";
            }
        } else {
            std::cout << "Invalid choice!\n";
        }
    }

    void run() {
        int choice;
        
        std::cout << "Welcome to the Smart Traffic Management System!\n";
        
        do {
            displayMainMenu();
            std::cin >> choice;
            
            switch (choice) {
                case 1:
                    startSystem();
                    break;
                case 2:
                    addIntersection();
                    break;
                case 3:
                    addVehicle();
                    break;
                case 4:
                    addEmergencyVehicle();
                    break;
                case 5:
                    displayStatus();
                    break;
                case 6:
                    generateReport();
                    break;
                case 7:
                    runDemoSimulation();
                    break;
                case 8:
                    configureIntersection();
                    break;
                case 9:
                    stopSystem();
                    break;
                case 0:
                    std::cout << "Exiting system...\n";
                    if (demoRunning) {
                        stopSystem();
                    }
                    break;
                default:
                    std::cout << "Invalid choice! Please try again.\n";
                    break;
            }
            
            if (choice != 0) {
                std::cout << "\nPress Enter to continue...";
                std::cin.ignore();
                std::cin.get();
            }
            
        } while (choice != 0);
    }
};

int main() {
    try {
        TrafficManagementDemo demo;
        demo.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}