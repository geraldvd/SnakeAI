#
# Main CMakeLists.txt, to build the SnakeAI project using CMake (www.cmake.org)
#
# Author: Gerald van Dalen
# Started project: 09/02/2016
# Last edited: 10/02/2016
#########################################################################
### Basic setup cmake
cmake_minimum_required(VERSION 2.8.11)
project(SnakeAI)

# Version
set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "1")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(PROJECT_VERSION_FULL "${PROJECT_VERSION}.${PROJECT_VERSION_PATCH}")

# OSX Warning fix
set(CMAKE_MACOSX_RPATH 1)

# C++11 support
add_definitions(-std=c++11)

# Show all warnings
add_definitions(-Wall)

# Enable debug mode
set(CMAKE_CONFIGURATION_TYPES Debug Minsizerel Release RelWithDebInfo CACHE STRING
        "List of possible configurations" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the type of build, options are: Debug MinSizeRel Release RelWithDebInf" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Set paths
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin CACHE PATH "Build directory")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

## Specify cmake search directory
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/src/3rdParty/cmake")
#list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/src/3rdParty")

#########################################################################
### Configuration options
option(WITH_QT "Should the executable have the Qt libraries (and hence a GUI)?" OFF)
option(WITH_OPENCV "Should the executable have the OpenCV libraries (alternative GUI and keyboard interaction)?" ON)
option(WITH_TESTS "Should unittests be compiled?" OFF)

option(WITH_RL "Should RL be used to play the game (i.e., extra executable)?" ON)

#########################################################################
### Qt 5 settings
if(WITH_QT)
    if(APPLE)
        set(BASE_DIR_QT5 "/Applications/Qt/5.4/clang_64" CACHE FILEPATH "The full path to the Qt 5 installation (OSX)")
    else(APPLE)
        set(BASE_DIR_QT5 "/opt/Qt/5.4/gcc_64" CACHE FILEPATH "The full path to the Qt 5 installation (Linux)")
    endif(APPLE)
endif(WITH_QT)

#########################################################################
### OpenCV settings
if(WITH_OPENCV)
    find_package(OpenCV REQUIRED)
endif(WITH_OPENCV)


#########################################################################
# Add sources
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
add_subdirectory(src)

# Add tests
if(WITH_TESTS)
    add_subdirectory(tests)
    include_directories(tests)
endif(WITH_TESTS)
