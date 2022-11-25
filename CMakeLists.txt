# =================================== PREAMBULE ===================================

cmake_minimum_required(VERSION 3.11.0)
project(ChestnutGameEngine VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

if(MSVC)
    include(GenerateExportHeader)
endif()




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





# ========================== PROJECT OPTIONS AND VARIABLES ============================

# add debug define
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DCHESTNUT_DEBUG")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCHESTNUT_DEBUG")
endif()


set(CHESTNUT_ENGINE_COMPILE_OPTIONS_GNU     -Wall -Wpedantic -Wno-unused-variable)

# 4100, 4101 - unused variables
# 4251 - x needs to have dll interface
#   This shows up even for private members which just happened to be STL objects
#   You can make the warning go away by exporting individual methods instead of the entire class,
#   but this lib is not intended to be C-compatible, so these warnings should be ignored.
# 4834 - ignored [[nodiscard]] - this comes from tl::typelist
set(CHESTNUT_ENGINE_COMPILE_OPTIONS_MSVC    /W3 /wd4100 /wd4101 /wd4834 /wd4251)


option(CHESTNUT_BUILD_TESTS "Build ChestnutGameEngine project tests" ON)





# =================================== DEPENDENCIES ===================================

# establish FetchContent dependencies

FetchContent_Declare(
    chestnut-ecs
    GIT_REPOSITORY https://github.com/SpontanCombust/chestnut-ecs
    GIT_TAG v1.1.2
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


# configure lib options
set(SDL2TTF_INSTALL OFF)
set(SDL2TTF_SAMPLES OFF)

set(SDL2MIXER_INSTALL OFF)
set(SDL2MIXER_SAMPLES OFF)

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






# ====================================== CGE LIBRARIES ======================================

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
    # 4251 - x needs to have dll interface
    #   This shows up even for private members which just happened to be STL objects
    #   You can make the warning go away by exporting individual methods instead of the entire class,
    #   but this lib is not intended to be C-compatible, so these warnings should be ignored.
    # 4834 - ignored [[nodiscard]] - this comes from tl::typelist
    $<$<CXX_COMPILER_ID:MSVC>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_MSVC}>

    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_GNU}>
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
    imgui
    nativefiledialog
    nlohmann_json
)

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})








# ========================================= TESTS ======================================

if(CHESTNUT_BUILD_TESTS)
    add_executable(${PROJECT_NAME}_Test)
    add_subdirectory(tests)

    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v2.13.7
    )

    FetchContent_MakeAvailable(catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
        

    target_compile_options(${PROJECT_NAME}_Test PRIVATE
        # 4100, 4101 - unused variables
        # 4251 - x needs to have dll interface
        # 4834 - ignored [[nodiscard]]
        $<$<CXX_COMPILER_ID:MSVC>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_MSVC}>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_GNU}>
    )

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
endif()
