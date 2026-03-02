cmake_minimum_required(VERSION 3.20)
project(Galaga_CIS376_2DGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/game-items)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# -----------------------
# Your executable
# -----------------------
add_executable(main
  main.cpp
  Enemy.cpp
  Player.cpp
  Projectile.cpp
)
set(SDL_SHARED  OFF CACHE BOOL "" FORCE)   # build as static lib
set(SDL_STATIC  ON  CACHE BOOL "" FORCE)
set(SDL_TEST    OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL3)
 
# Box2D v3.1.0
FetchContent_Declare(
    box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG        v3.1.0
    GIT_SHALLOW    TRUE
)
set(BOX2D_SAMPLES OFF CACHE BOOL "" FORCE)
set(BOX2D_UNIT_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(box2d)
 
# Executable 
add_executable(main main.cpp Player.cpp Enemy.cpp Projectile.cpp Score.cpp)
 
target_link_libraries(main
    PRIVATE
        SDL3::SDL3-static
        box2d
)
 
target_compile_options(main PRIVATE)

# Link SDL3 + SDL3_image
target_link_libraries(main PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
