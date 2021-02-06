cmake_minimum_required(VERSION 3.0.0)
project(ChestnutGameEngine VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cmake/sdl2)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp )
include_directories(${PROJECT_NAME} src )

target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wpedantic -DCHESTNUT_DEBUG>)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Image)

# find_package(SDL2_ttf REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# find_package(SDL2_mixer REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

install(TARGETS ${PROJECT_NAME} CONFIGURATIONS Debug RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin/Debug)
install(TARGETS ${PROJECT_NAME} CONFIGURATIONS Release RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin/Release)