# 1. Define the executable and list the source files
add_executable(ConsoleAdventure
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
)

# 2. Add root include directory for the game
target_include_directories(ConsoleAdventure PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# 3. Link against the engine library
target_link_libraries(ConsoleAdventure PRIVATE
    Engine
)
