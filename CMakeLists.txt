cmake_minimum_required(VERSION 3.0.0)
project(ChestnutGameEngine VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")
add_executable(${PROJECT_NAME} ${SOURCES})
include_directories(${PROJECT_NAME} include)

target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wpedantic -DCHESTNUT_DEBUG>)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Image)

# find_package(SDL2_ttf REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# find_package(SDL2_mixer REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::Mixer)


# target_link_libraries()