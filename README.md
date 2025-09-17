# Smart Traffic Management System

A comprehensive C++ implementation of an intelligent traffic management system that optimizes traffic flow, handles emergency vehicles, and provides real-time monitoring and analytics.

## 🚦 Features

- **Multi-Intersection Management**: Control multiple traffic intersections simultaneously
- **Emergency Vehicle Priority**: Automatic detection and priority routing for emergency vehicles
- **Adaptive Signal Timing**: Dynamic adjustment based on traffic density and time-of-day
- **Real-time Monitoring**: Live traffic statistics and system status
- **Vehicle Simulation**: Automatic traffic generation for testing and demonstration
- **Comprehensive Reporting**: Detailed analytics and performance metrics
- **Interactive Console Interface**: User-friendly menu system for system control

## 📋 System Requirements

- **C++ Compiler**: C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- **CMake**: Version 3.10 or higher
- **Operating System**: Windows, Linux, or macOS
- **Memory**: Minimum 100MB RAM
- **Threading Support**: std::thread compatible system

## 🏗️ Project Structure

```
Smart Traffic Management System/
├── src/                    # Source files (.cpp)
│   ├── TrafficLight.cpp
│   ├── Vehicle.cpp
│   ├── TrafficSensor.cpp
│   ├── Intersection.cpp
│   ├── TrafficStats.cpp
│   └── TrafficController.cpp
├── include/                # Header files (.h)
│   ├── TrafficLight.h
│   ├── Vehicle.h
│   ├── TrafficSensor.h
│   ├── Intersection.h
│   ├── TrafficStats.h
│   └── TrafficController.h
├── build/                  # Build output directory
├── .github/
│   └── copilot-instructions.md
├── CMakeLists.txt         # CMake build configuration
├── main.cpp               # Main application entry point
└── README.md              # This file
```

## 🔧 Build Instructions

### Prerequisites

1. **C++ Compiler** (Choose one):
   - **Windows**: 
     - MinGW-w64: Download from [winlibs.com](https://winlibs.com/) or [msys2.org](https://www.msys2.org/)
     - Visual Studio 2017+ with C++ Build Tools
     - Clang/LLVM: Download from [llvm.org](https://llvm.org/)
   - **Linux**: GCC 7+ (`sudo apt-get install build-essential`)
   - **macOS**: Xcode Command Line Tools (`xcode-select --install`)

2. **CMake** (Optional, for advanced builds):
   - Windows: Download from [cmake.org](https://cmake.org/download/)
   - Linux: `sudo apt-get install cmake` (Ubuntu/Debian) or `sudo yum install cmake` (CentOS/RHEL)
   - macOS: `brew install cmake`

### Build Steps

#### Method 1: Simple Build (Recommended)

**For Windows:**
```bash
# Run the build script
.\build.bat
```

**For Linux/macOS:**
```bash
# Make script executable and run
chmod +x build.sh
./build.sh
```

#### Method 2: Manual Compilation

**Windows (with MinGW):**
```bash
mkdir build
cd build
g++ -std=c++17 -pthread -I../include -o smart_traffic_system.exe ../main.cpp ../src/*.cpp
```

**Windows (with MSVC):**
```bash
mkdir build
cd build
cl /std:c++17 /EHsc /I..\include ..\main.cpp ..\src\*.cpp /Fe:smart_traffic_system.exe
```

**Linux/macOS:**
```bash
mkdir build
cd build
g++ -std=c++17 -pthread -I../include -o smart_traffic_system ../main.cpp ../src/*.cpp
```

#### Method 3: CMake Build (Advanced)

1. **Navigate to project directory**:
   ```bash
   cd "d:\PBL Microproject"
   ```

2. **Create and navigate to build directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Configure the project**:
   ```bash
   cmake ..
   ```

4. **Build the project**:
   ```bash
   cmake --build .
   ```

5. **Run the application**:
   ```bash
   # Windows
   .\smart_traffic_system.exe
   
   # Linux/macOS
   ./smart_traffic_system
   ```

### Troubleshooting Build Issues

1. **No compiler found**: Install MinGW-w64, Visual Studio Build Tools, or GCC
2. **C++17 errors**: Ensure your compiler supports C++17 (GCC 7+, Clang 5+, MSVC 2017+)
3. **Threading errors**: Make sure pthread library is available
4. **Permission denied**: Run terminal as administrator (Windows) or use `sudo` (Linux/macOS)

### Alternative Build Commands

**For Release build**:
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

**For Debug build**:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug
```

**Using CMake target**:
```bash
cmake --build . --target run
```

## 🚀 Usage Guide

### Main Menu Options

1. **Start Traffic System**: Initialize and start the traffic management system
2. **Add Intersection**: Create new traffic intersections
3. **Add Vehicle**: Manually add vehicles to the system
4. **Add Emergency Vehicle**: Add emergency vehicles with priority handling
5. **Display System Status**: View current system state and statistics
6. **Generate Report**: Create detailed performance reports
7. **Run Demo Simulation**: Automated 30-second traffic simulation
8. **Configure Intersection**: Adjust traffic light timing
9. **Stop System**: Halt the traffic management system
0. **Exit**: Close the application

### Quick Start Guide

1. **Launch the application**
2. **Select option 1** to start the traffic system
3. **Select option 7** to run a demo simulation
4. **Select option 6** to view the generated report

### Adding Custom Traffic

1. Start the system (option 1)
2. Add vehicles (option 3) or emergency vehicles (option 4)
3. Monitor real-time status (option 5)
4. Generate performance reports (option 6)

## 🏛️ System Architecture

### Core Classes

#### TrafficLight
- Controls traffic signal states (Red, Yellow, Green, Flashing)
- Manages timing and emergency overrides
- Supports directional traffic control

#### Vehicle
- Represents different vehicle types (Car, Truck, Bus, Emergency vehicles)
- Priority-based queuing system
- Wait time tracking and analytics

#### TrafficSensor
- Vehicle detection simulation
- Traffic density calculation
- Real-time monitoring capabilities

#### Intersection
- Multi-directional traffic light coordination
- Vehicle queue management
- Phase-based signal timing

#### TrafficController
- System-wide traffic optimization
- Emergency vehicle coordination
- Multi-threading support for real-time operation

#### TrafficStats
- Comprehensive performance metrics
- Real-time analytics
- Report generation and file export

### Design Patterns Used

- **Strategy Pattern**: Different vehicle types and priorities
- **Observer Pattern**: Real-time status updates
- **State Pattern**: Traffic light state management
- **Factory Pattern**: Vehicle and intersection creation
- **Singleton Pattern**: System-wide traffic controller

## 📊 Features in Detail

### Emergency Vehicle Priority
- Automatic detection of emergency vehicles
- Immediate signal override for emergency directions
- Return to normal operation after emergency clearance

### Adaptive Traffic Control
- Real-time queue length analysis
- Dynamic signal timing adjustment
- Time-of-day optimization (rush hour detection)

### Performance Analytics
- Average wait time calculation
- System throughput measurement
- Direction-wise traffic analysis
- Emergency response rate tracking

### Multi-Threading Support
- Real-time signal control
- Concurrent traffic simulation
- Non-blocking user interface

## 🛠️ Configuration Options

### Traffic Light Timing
- Configurable green, yellow, and red durations
- Direction-specific timing settings
- Emergency override capabilities

### Simulation Parameters
- Traffic generation rates
- Vehicle type distribution
- Emergency vehicle frequency

### System Settings
- Real-time vs. accelerated simulation
- Multi-intersection coordination
- Performance optimization levels

## 📈 Performance Metrics

The system tracks and reports:
- **Total vehicles processed**
- **Average wait times**
- **System throughput** (vehicles per minute)
- **Emergency response efficiency**
- **Direction-wise traffic distribution**
- **Signal cycle optimization**

## 🔍 Troubleshooting

### Common Build Issues

1. **CMake not found**: Ensure CMake is installed and in PATH
2. **Compiler errors**: Verify C++17 support in your compiler
3. **Threading errors**: Ensure pthread library is available (Linux)
4. **Permission errors**: Run with appropriate permissions

### Runtime Issues

1. **Application crashes**: Check system resources and threading support
2. **Poor performance**: Reduce simulation speed or vehicle generation rate
3. **Display issues**: Ensure console supports UTF-8 characters

## 🤝 Contributing

This project follows standard C++ development practices:
- Use RAII principles
- Follow const-correctness
- Implement proper error handling
- Maintain clean separation of concerns
- Document public interfaces

## 📝 Class Diagram

```
┌──────────────────┐    ┌──────────────────┐    ┌──────────────────┐
│   TrafficLight   │    │     Vehicle      │    │   Intersection   │
├──────────────────┤    ├──────────────────┤    ├──────────────────┤
│- state: State    │    │- id: string      │    │- id: string      │
│- duration: int   │    │- type: VehType   │    │- lights: vector  │
│- timeLeft: int   │    │- priority: int   │    │- sensors: vector │
├──────────────────┤    │- direction: Dir  │    │- queues: vector  │
│+ changeState()   │    ├──────────────────┤    ├──────────────────┤
│+ update()        │    │+ isEmergency()   │    │+ updateSignals() │
│+ getState()      │    │+ getPriority()   │    │+ addVehicle()    │
└──────────────────┘    └──────────────────┘    │+ processTraffic()│
                                                 └──────────────────┘
         │                        │                        │
         └────────────────────────┼────────────────────────┘
                                  │
                    ┌──────────────────┐
                    │ TrafficSensor    │
                    ├──────────────────┤
                    │+ detectVehicle() │
                    │+ getCount()      │
                    └──────────────────┘
                              │
            ┌─────────────────────────────────┐
            │    TrafficController            │
            ├─────────────────────────────────┤
            │+ addIntersection()              │
            │+ handleEmergency()              │
            │+ optimizeTraffic()              │
            │+ generateReport()               │
            └─────────────────────────────────┘
                              │
                    ┌──────────────────┐
                    │  TrafficStats    │
                    ├──────────────────┤
                    │+ updateStats()   │
                    │+ generateReport()│
                    │+ saveToFile()    │
                    └──────────────────┘
```

## 📄 License

This project is developed as an educational demonstration of traffic management systems using C++17 features and modern software engineering practices.

## 📞 Support

For technical support or questions about the implementation:
1. Check the troubleshooting section above
2. Review the code comments and documentation
3. Ensure all dependencies are properly installed
4. Verify system requirements are met

---

**Version**: 1.0.0  
**Last Updated**: September 2025  
**Language**: C++17  
**Build System**: CMake 3.10+