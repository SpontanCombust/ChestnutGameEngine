cmake_minimum_required(VERSION 3.11.0)
project(ChestnutGameEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

if(MSVC)
    include(GenerateExportHeader)
endif()


# =================================== Allow offline mode ===================================

FetchContent_Declare(
    FetchContentOffline
    GIT_REPOSITORY https://github.com/SpontanCombust/cmake-fetchcontent-offline
)
set(FETCHCONTENT_UPDATES_DISCONNECTED_FETCHCONTENTOFFLINE ON)
FetchContent_MakeAvailable(FetchContentOffline)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${fetchcontentoffline_SOURCE_DIR}")
include(fetchcontent-offline)

FetchContent_DisconnectedIfOffline()



# =================================== Library dependencies ===================================

# establish FetchContent dependencies

FetchContent_Declare(
    chestnut-ecs
    GIT_REPOSITORY https://github.com/SpontanCombust/ChestnutECSCore
    GIT_TAG rework #TODO change to tag when version is complete
)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.24.2
)
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/SpontanCombust/SDL_ttf
    GIT_TAG 3d0165360d99ddc3a72a5472e408b7d962973fbb
)
FetchContent_Declare(
    SDL2_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
    GIT_TAG c40dc4397a8cfd66ce82fbb1ba4cfcdb89723a53
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
FetchContent_Declare(
    Assimp
    GIT_REPOSITORY https://github.com/assimp/assimp
    GIT_TAG v5.2.5
)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
    GIT_TAG master
)


# configure lib options
set(TTF_DISABLE_INSTALL ON)
set(OPTIONAL_BUILD_TESTS OFF)
set(EXPECTED_BUILD_TESTS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)

if(UNIX)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()


# finally fetch and configure the dependencies
FetchContent_MakeAvailable(
    chestnut-ecs 
    SDL2 
    SDL2_ttf 
    SDL2_mixer
    tl_optional
    tl_expected
    Assimp
    stb
)

find_package(OpenGL REQUIRED)

add_library(glad STATIC)
target_sources(glad PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/src/glad.c)
target_include_directories(glad PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include)

add_library(stb_image INTERFACE)
target_sources(stb_image INTERFACE ${stb_SOURCE_DIR}/stb_image.h)
target_include_directories(stb_image INTERFACE ${stb_SOURCE_DIR})





# ====================================== CGE library ======================================

add_library(${PROJECT_NAME} SHARED)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src )
add_subdirectory(src/chestnut/engine)

if(MSVC)
    GENERATE_EXPORT_HEADER(
        ${PROJECT_NAME}
        BASE_NAME ${PROJECT_NAME}
        EXPORT_MACRO_NAME CHESTNUT_API
        EXPORT_FILE_NAME ChestnutGameEngine_EXPORTS.h
        STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
    )
endif()

target_compile_options(${PROJECT_NAME} PRIVATE
    # 4100, 4101 - unused variables
    # 4834 - ignored [[nodiscard]]
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /wd4100 /wd4101 /wd4834>

    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wpedantic -Wno-unused-variable>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${OPENGL_LIBRARIES}
    glad
    chestnut-ecs
    SDL2
    SDL2_ttf
    SDL2_mixer
    optional
    expected
    assimp
    stb_image
)

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})

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
    
    
target_link_libraries(${PROJECT_NAME}_Test 
    ${PROJECT_NAME} 
    Catch2::Catch2
)

# copy DLLs
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME}_Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2>       $<TARGET_FILE_DIR:${PROJECT_NAME}_Test>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2_ttf>   $<TARGET_FILE_DIR:${PROJECT_NAME}_Test>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2_mixer> $<TARGET_FILE_DIR:${PROJECT_NAME}_Test>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:assimp>     $<TARGET_FILE_DIR:${PROJECT_NAME}_Test>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:freetype>   $<TARGET_FILE_DIR:${PROJECT_NAME}_Test>
    )
endif()

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME}_Test)

