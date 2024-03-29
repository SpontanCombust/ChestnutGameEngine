add_executable(ChestnutGameEngine_Graphics3D_Test)
    
target_link_libraries(ChestnutGameEngine_Graphics3D_Test 
    ChestnutGameEngine_Graphics3D
    Catch2::Catch2
)

target_include_directories(ChestnutGameEngine_Graphics3D_Test PRIVATE
    ${CHESTNUT_ENGINE_LIB_INCLUDE_DIR}
    ${CHESTNUT_TEST_COMMON_INCLUDE_DIR}
)


target_compile_options(ChestnutGameEngine_Graphics3D_Test PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_MSVC}>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_GNU}>
)

set_target_properties(ChestnutGameEngine_Graphics3D_Test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CHESTNUT_ENGINE_BIN_DIR}
)

catch_discover_tests(ChestnutGameEngine_Graphics3D_Test)


# copy DLLs
if(WIN32)
    copy_shared_libs(TARGET ChestnutGameEngine_Graphics3D_Test DEPENDENCIES
        SDL2
        SDL2_ttf
        SDL2_mixer
        freetype
        assimp
        ChestnutGameEngine
        ChestnutGameEngine_Graphics3D
    )
endif()


target_sources(ChestnutGameEngine_Graphics3D_Test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/camera3d_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/extrude_profile_test.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/phong_renderer_test.cpp
    ${CHESTNUT_TEST_COMMON_SOURCES}
)
