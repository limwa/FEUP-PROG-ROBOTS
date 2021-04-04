cmake_minimum_required(VERSION 3.0.0)
project(robots VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(robots src/main.cpp src/game.cpp src/files.cpp src/info.cpp src/keyboard.cpp src/logic.cpp src/mazes.cpp src/screen.cpp src/timer.cpp src/utf8.cpp)
include_directories(robots include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
