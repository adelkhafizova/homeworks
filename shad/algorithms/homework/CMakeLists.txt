cmake_minimum_required(VERSION 3.3)
project(homework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES
#    football_crew.cpp
#    mainA.cpp
#    mainC.cpp
#    mainD.cpp
#    testMainD.cpp)

add_executable(football_crew football_crew.cpp)
add_executable(mainA mainA.cpp)
add_executable(mainC mainC.cpp)
add_executable(mainD mainD.cpp)
add_executable(testMainD testMainD.cpp)