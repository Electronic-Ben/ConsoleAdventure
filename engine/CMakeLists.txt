add_library(Engine STATIC
    src/Keyboard.cpp
    src/Menu.cpp
    src/ProgressBar.cpp
    src/Screen.cpp
    src/World.cpp
    src/SelectMenu.cpp
)

# PUBLIC ensures any target linking Engine automatically gets the project root include directory
target_include_directories(Engine PUBLIC
    ${CMAKE_SOURCE_DIR}
)

