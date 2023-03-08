# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

#enforce C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the project name
project (garage_door_fsm)

enable_testing()
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
# Create a sources variable with a link to all cpp files to compile
set(SOURCES
        src/garage_door.cpp
        include/garage_door.h
)


add_library(garage_door src/garage_door.cpp include/garage_door.h)
target_link_libraries(garage_door ${CURSES_LIBRARIES})

# Add an executable with the above sources
add_executable(main src/main.cpp src/garage_door.cpp include/garage_door.h)
target_link_libraries(main ${CURSES_LIBRARIES})


#test executables
add_executable(test_run tests/test_run.cpp src/garage_door.cpp include/garage_door.h)
target_link_libraries(test_run ${CURSES_LIBRARIES})


#add test
add_test(NAME test_run
        COMMAND test_run)


#hide test executables
set_target_properties(
    test_run
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY bin/tests
)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
#target_include_directories(test_matrix
#    PRIVATE 
#        ${PROJECT_SOURCE_DIR}/include
#)
