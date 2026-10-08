add_library(engine STATIC
    src/Keyboard.cpp
    src/Menu.cpp
    src/World.cpp
    src/Container.cpp
)

# PUBLIC ensures any target linking engine automatically gets the project root include directory
target_include_directories(engine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine PUBLIC cpp-terminal)
