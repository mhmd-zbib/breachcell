cmake_minimum_required(VERSION 3.16)
project(CppProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

file(GLOB ENGINE_SRC
    "engine/*.cpp"
    "engine/graphics/*.cpp"
    "engine/input/*.cpp"
    "engine/utils/*.cpp"
    "engine/ecs/components/*.cpp"
    "engine/ecs/systems/*.cpp"
    "engine/ecs/entity_manager.cpp"
)
file(GLOB GAME_SRC
    "game/*.cpp"
    "game/entities/*.cpp"
)

add_executable(CppProject
    main.cpp
    ${ENGINE_SRC}
    ${GAME_SRC}
)

target_include_directories(CppProject PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(CppProject PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
