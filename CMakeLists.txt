cmake_minimum_required(VERSION 3.0.0)
project(ChestnutGameEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# =================================== Library dependencies ===================================

include(FetchContent)
# set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

FetchContent_Declare(
    ChestnutECSCore
    GIT_REPOSITORY https://github.com/SpontanCombust/ChestnutECSCore
    GIT_TAG master #TODO will need version tag for ECS library!
)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.0.16
)
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG release-2.0.5
)
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
    GIT_TAG release-2.0.15
)
FetchContent_Declare(
    SDL2_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
    GIT_TAG release-2.0.4
)
FetchContent_Declare(
    tl_optional
    GIT_REPOSITORY https://github.com/TartanLlama/optional
    GIT_TAG master # the latest version tags for tl's libraries link to very old commits with bad CMakeLists.txt
)
FetchContent_Declare(
    tl_expected
    GIT_REPOSITORY https://github.com/TartanLlama/expected
    GIT_TAG master
)

FetchContent_MakeAvailable(
    ChestnutECSCore 
    SDL2 
    SDL2_image 
    SDL2_ttf 
    SDL2_mixer
    tl_optional
    tl_expected
)


# findOpenGL and findGLEW should come with CMake installation
if(UNIX)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)


# configure libs
set(OPTIONAL_BUILD_TESTS OFF)
set(EXPECTED_BUILD_TESTS OFF)

# ====================================== CGE library ======================================

add_library(${PROJECT_NAME} SHARED)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src )
add_subdirectory(src/chestnut/engine)

target_compile_options(${PROJECT_NAME} PUBLIC $<$<CONFIG:DEBUG>:-Wall -Wpedantic -DCHESTNUT_DEBUG>)


target_link_libraries(${PROJECT_NAME} 
    ChestnutECSCore
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    optional
    expected
)

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})




# ====================================== Tests executable ======================================

add_executable(${PROJECT_NAME}_Test)
add_subdirectory(tests)

include(FetchContent)

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG v2.13.7
)

FetchContent_MakeAvailable(catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
    
    
target_link_libraries(${PROJECT_NAME}_Test ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_Test Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}_Test)

