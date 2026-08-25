add_library(Engine STATIC
    src/keyboard.cpp
    src/ProgressBar.cpp
    src/Screen.cpp
    src/Selectmenu.cpp
    src/World.cpp
)

# PUBLIC ensures any target linking Engine automatically gets the project root include directory
target_include_directories(Engine PUBLIC
    ${CMAKE_SOURCE_DIR}
)

