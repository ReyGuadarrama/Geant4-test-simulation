#Specify the minimum required version of cmake to compile the program
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

#Name of the project
project(Simulation)

#Find Geant4 package and the user interface and visualization drivers
find_package(Geant4 REQUIRED ui_all vis_all)

#Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

#Locate sources and headers folders for the project
include_directories(${PROJECT_SOURCE_DIR}/inc
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIRS})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)

#Add executables and link it to the Geant4 libraries
add_executable(testSimulation testSimulation.cc ${sources} ${headers})
target_link_libraries(testSimulation ${Geant4_LIBRARIES})
add_custom_target(Simulation DEPENDS testSimulation)