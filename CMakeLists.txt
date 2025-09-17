cmake_minimum_required(VERSION 3.10)

# Project name and version
project(SmartTrafficManagement VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler-specific options
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/TrafficLight.cpp
    src/Vehicle.cpp
    src/TrafficSensor.cpp
    src/Intersection.cpp
    src/TrafficStats.cpp
    src/TrafficController.cpp
    main.cpp
)

# Header files
set(HEADERS
    include/TrafficLight.h
    include/Vehicle.h
    include/TrafficSensor.h
    include/Intersection.h
    include/TrafficStats.h
    include/TrafficController.h
)

# Create executable
add_executable(smart_traffic_system ${SOURCES} ${HEADERS})

# Find and link threading library
find_package(Threads REQUIRED)
target_link_libraries(smart_traffic_system Threads::Threads)

# Set output directory
set_target_properties(smart_traffic_system PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy executable to build root for easier access
add_custom_command(TARGET smart_traffic_system POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:smart_traffic_system> ${CMAKE_BINARY_DIR}/
)

# Installation (optional)
install(TARGETS smart_traffic_system
    RUNTIME DESTINATION bin
)

# Create build info
configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/version.h.in"
    "${CMAKE_BINARY_DIR}/version.h"
    @ONLY
)

# Print build information
message(STATUS "Smart Traffic Management System")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Source directory: ${CMAKE_SOURCE_DIR}")
message(STATUS "Binary directory: ${CMAKE_BINARY_DIR}")

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    set_target_properties(smart_traffic_system PROPERTIES
        WIN32_EXECUTABLE FALSE  # Console application
    )
    message(STATUS "Platform: Windows")
elseif(UNIX)
    # Unix/Linux-specific settings
    message(STATUS "Platform: Unix/Linux")
endif()

# Debug information
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build enabled")
    target_compile_definitions(smart_traffic_system PRIVATE DEBUG_BUILD)
endif()

# Add custom target for running the application
add_custom_target(run
    COMMAND smart_traffic_system
    DEPENDS smart_traffic_system
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Smart Traffic Management System..."
)

# Add custom target for cleaning build files
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning all build files..."
)