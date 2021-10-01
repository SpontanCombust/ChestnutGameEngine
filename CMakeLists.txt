cmake_minimum_required(VERSION 3.0.0)
project(ChestnutGameEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cmake/sdl2)


# =================================== Finding libraries ===================================

find_package(SDL2 REQUIRED)

find_package(SDL2_image REQUIRED)

find_package(SDL2_ttf REQUIRED)

# find_package(SDL2_mixer REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)


# ====================================== CGE library ======================================

add_library(${PROJECT_NAME} SHARED)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src )
add_subdirectory(src/chestnut/engine)

target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wpedantic -DCHESTNUT_DEBUG>)


add_subdirectory(dependencies/ChestnutECSCore)
target_link_libraries(${PROJECT_NAME} ChestnutECSCore)

target_link_libraries(${PROJECT_NAME} SDL2::Main)
target_link_libraries(${PROJECT_NAME} SDL2::Image)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)
# target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})

#TODO readd install targets later

# ====================================== Tests executable ======================================

add_executable(${PROJECT_NAME}_Test)

target_link_libraries(${PROJECT_NAME}_Test ${PROJECT_NAME})

add_subdirectory(tests)

find_package(Catch2)

target_link_libraries(${PROJECT_NAME}_Test ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_Test Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}_Test)

