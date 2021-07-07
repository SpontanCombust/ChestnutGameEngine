cmake_minimum_required(VERSION 3.0.0)
project(ChestnutGameEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cmake/sdl2)

# ====================================== CGE library ======================================

add_library(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src )
add_subdirectory(src)

target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wpedantic -DCHESTNUT_DEBUG>)

install(TARGETS ${PROJECT_NAME} CONFIGURATIONS Debug RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/lib)
install(TARGETS ${PROJECT_NAME} CONFIGURATIONS Release RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/lib)


set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRECTORIES})

# ====================================== Tests executable ======================================

add_executable(Tests ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_include_directories(Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Tests ${PROJECT_NAME})
add_subdirectory(tests)

install(TARGETS Tests CONFIGURATIONS Debug RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS Tests CONFIGURATIONS Release RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)
target_link_libraries(Tests SDL2::Main)

find_package(SDL2_image REQUIRED)
target_link_libraries(Tests SDL2::Image)

find_package(SDL2_ttf REQUIRED)
target_link_libraries(Tests SDL2::TTF)

# find_package(SDL2_mixer REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
target_include_directories(Tests PUBLIC ${OPENGL_INCLUDE_DIRS})
target_link_libraries(Tests ${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
target_include_directories(Tests PUBLIC ${GLEW_INCLUDE_DIRECTORIES})
target_link_libraries(Tests ${GLEW_LIBRARIES})