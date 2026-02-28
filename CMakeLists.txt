cmake_minimum_required(VERSION 3.20)
project(Galaga_CIS376_2DGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include(FetchContent)

# -----------------------
# Fetch SDL3
# -----------------------
#FetchContent_Declare(
#  SDL3
#  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
#  GIT_TAG release-3.2.0   # You can change this tag
#)
#FetchContent_MakeAvailable(SDL3)

# -----------------------
# Fetch SDL3_image
# -----------------------
#FetchContent_Declare(
#  SDL3_image
#  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
#  GIT_TAG release-3.2.0   # Match SDL3_image release when possible
#)
#FetchContent_MakeAvailable(SDL3_image)

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

# Link SDL3 + SDL3_image
target_link_libraries(main PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)