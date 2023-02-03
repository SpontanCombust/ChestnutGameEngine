add_library(ChestnutGameEngine_Graphics3D SHARED)

target_include_directories(ChestnutGameEngine_Graphics3D PUBLIC 
    ${CHESTNUT_ENGINE_LIB_INCLUDE_DIR}
)

target_link_libraries(ChestnutGameEngine_Graphics3D PUBLIC 
    ${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    glad
    chestnut-ecs
    SDL2
    SDL2_ttf
    SDL2_mixer
    optional
    expected
    stb_image
    imgui
    nativefiledialog
    nlohmann_json
    assimp
)


target_compile_options(ChestnutGameEngine_Graphics3D PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_MSVC}>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_GNU}>
)



target_sources(ChestnutGameEngine_Graphics3D PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/macros.hpp
)

add_subdirectory(graphics)
add_subdirectory(resources)