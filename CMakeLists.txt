cmake_minimum_required(VERSION 3.20)
project(BouncingBalls CXX)
 
set(CMAKE_CXX_STANDARD 17)
 
include(FetchContent)
 
# SDL3
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.8
    GIT_SHALLOW    TRUE
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
add_executable(main main.cpp Player.cpp Enemy.cpp Projectile.cpp)
 
target_link_libraries(main
    PRIVATE
        SDL3::SDL3-static
        box2d
)
 
target_compile_options(main PRIVATE)