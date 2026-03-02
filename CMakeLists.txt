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
  Score.cpp
)

# Link SDL3 + SDL3_image
target_link_libraries(main PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)