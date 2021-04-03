cmake_minimum_required(VERSION 3.0.0)
project(robots VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(robots src/main.cpp src/entities.cpp src/game.cpp)
include_directories(robots include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
