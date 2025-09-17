<!-- Use this file to provide workspace-specific custom instructions to Copilot. For more details, visit https://code.visualstudio.com/docs/copilot/copilot-customization#_use-a-githubcopilotinstructionsmd-file -->

## Smart Traffic Management System - C++ Project

This workspace contains a C++ implementation of a Smart Traffic Management System with the following components:

### Project Structure
- `/src/` - Source files (.cpp)
- `/include/` - Header files (.h)
- `/build/` - Build output directory
- `CMakeLists.txt` - CMake build configuration
- `README.md` - Project documentation

### Core Classes
- `TrafficLight` - Traffic signal control
- `Vehicle` - Vehicle representation and types
- `Intersection` - Traffic intersection management
- `TrafficSensor` - Vehicle detection
- `TrafficController` - Main system controller
- `TrafficStats` - Statistics and reporting

### Development Guidelines
- Use C++17 features
- Follow RAII principles
- Implement proper error handling
- Use STL containers and algorithms
- Maintain clean separation of concerns
- Document public interfaces

### Build Instructions
1. Create build directory: `mkdir build && cd build`
2. Configure: `cmake ..`
3. Build: `cmake --build .`
4. Run: `./smart_traffic_system`

Project completed and ready for development.