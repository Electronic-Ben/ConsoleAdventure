cmake_minimum_required(VERSION 3.20)
project(ConsoleAdventure LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/cpp-terminal)
add_subdirectory(engine)
add_subdirectory(game)