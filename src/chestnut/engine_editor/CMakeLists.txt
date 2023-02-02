add_executable(ChestnutGameEngineEditor WIN32)

target_link_libraries(ChestnutGameEngineEditor 
    ChestnutGameEngine
)

target_include_directories(ChestnutGameEngineEditor PRIVATE
    ${CHESTNUT_LIB_INCLUDE_DIR}
)


target_compile_options(ChestnutGameEngineEditor PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_MSVC}>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_GNU}>
)

set_target_properties(ChestnutGameEngineEditor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

copy_shared_libs(TARGET ChestnutGameEngineEditor DEPENDENCIES
    ChestnutGameEngine
    SDL2
    SDL2_ttf
    SDL2_mixer
    freetype
)



target_sources(ChestnutGameEngineEditor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
