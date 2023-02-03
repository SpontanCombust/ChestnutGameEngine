include(FetchContent)

# =============================== ALLOW OFFLINE MODE ===================================

FetchContent_Declare(
    FetchContentOffline
    GIT_REPOSITORY https://github.com/SpontanCombust/cmake-fetchcontent-offline
)
set(FETCHCONTENT_UPDATES_DISCONNECTED_FETCHCONTENTOFFLINE ON)
FetchContent_MakeAvailable(FetchContentOffline)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${fetchcontentoffline_SOURCE_DIR}")
include(fetchcontent-offline)

FetchContent_DisconnectedIfOffline()




# =========================== DECLARE DEPENDENCY SOURCES ================================

FetchContent_Declare(
    chestnut-ecs
    GIT_REPOSITORY https://github.com/SpontanCombust/chestnut-ecs
    GIT_TAG v1.2.1
)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.24.2
)
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
    GIT_TAG release-2.20.1
)
FetchContent_Declare(
    SDL2_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
    GIT_TAG release-2.6.2
)
FetchContent_Declare(
    tl_optional
    GIT_REPOSITORY https://github.com/TartanLlama/optional
    GIT_TAG c28fcf74d207fc667c4ed3dbae4c251ea551c8c1 # 02/05/2021
)
FetchContent_Declare(
    tl_expected
    GIT_REPOSITORY https://github.com/TartanLlama/expected
    GIT_TAG b74fecd4448a1a5549402d17ddc51e39faa5020c # 24/11/2022
)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
    GIT_TAG 5736b15f7ea0ffb08dd38af21067c314d6a3aae9 # 30/01/2023
)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.88
)
FetchContent_Declare(
    nativefiledialog
    GIT_REPOSITORY https://github.com/SpontanCombust/nativefiledialog
    GIT_TAG CMakeLists
)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.2
)
FetchContent_Declare(
    Assimp
    GIT_REPOSITORY https://github.com/assimp/assimp
    GIT_TAG v5.2.5
)
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG v2.13.7
)




# ============================= SET DEPENDENCY OPTIONS ===============================

# configure lib options
set(SDL_SHARED ON)
set(SDL_STATIC OFF)
set(SDL_TEST OFF)

set(SDL2TTF_VENDORED ON)
set(SDL2TTF_INSTALL OFF)
set(SDL2TTF_SAMPLES OFF)

set(SDL2MIXER_VENDORED ON)
set(SDL2MIXER_INSTALL OFF)
set(SDL2MIXER_SAMPLES OFF)

set(OPTIONAL_BUILD_TESTS OFF)

set(EXPECTED_BUILD_TESTS OFF)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)

if(UNIX)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()




# ============================= FETCH DEPENDENCIES =================================

# finally fetch and configure the dependencies
FetchContent_MakeAvailable(
    chestnut-ecs 
    SDL2 
    SDL2_ttf 
    SDL2_mixer
    tl_optional
    tl_expected
    stb
    imgui
    nativefiledialog
    json
)

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
add_library(glad STATIC)
target_sources(glad PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/src/glad.c)
target_include_directories(glad PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include)

# stb
add_library(stb_image INTERFACE)
target_sources(stb_image INTERFACE ${stb_SOURCE_DIR}/stb_image.h)
target_include_directories(stb_image INTERFACE ${stb_SOURCE_DIR})

# imgui
add_library(imgui STATIC)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_sources(imgui PRIVATE
    ${imgui_SOURCE_DIR}/imconfig.h
    ${imgui_SOURCE_DIR}/imgui.h
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_internal.h
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
if(UNIX)
    target_link_libraries(imgui PRIVATE 
        SDL2
        ${OPENGL_LIBRARIES}
        ${CMAKE_DL_LIBS}
    )
else()
    target_link_libraries(imgui PRIVATE 
        SDL2
        ${OPENGL_LIBRARIES}
    )
endif()


# extension specific
if(CHESTNUT_BUILD_ENGINE_EXTENSIONS)
    FetchContent_MakeAvailable(Assimp)    
endif()

# test specific
if(CHESTNUT_BUILD_TESTS)
    FetchContent_MakeAvailable(catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
endif()
