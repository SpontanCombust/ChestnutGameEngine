add_executable(ChestnutGameEngine_Test)

target_link_libraries(ChestnutGameEngine_Test 
    ChestnutGameEngine
    Catch2::Catch2
)

target_compile_options(ChestnutGameEngine_Test PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_MSVC}>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_GNU}>
)

catch_discover_tests(ChestnutGameEngine_Test)


# copy DLLs
if(WIN32)
    copy_shared_libs(TARGET ChestnutGameEngine_Test DEPENDENCIES
        SDL2
        SDL2_ttf
        SDL2_mixer
        freetype
    )
endif()



target_sources(ChestnutGameEngine_Test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/audio_manager_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/colored_polygon2d_renderer_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/do_not_commit_this.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager_test.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/flags_test.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/framebuffer_test.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/math_matrix_3_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_matrix_4_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_matrix_n_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_2_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_3_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_4_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_cast_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_n_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_transform_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/physics_collision2d_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resource_manager_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resources_tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/serialization_tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_animation_system_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_rendering_system_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite_renderer_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text_renderer_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timer_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window_test.cpp
    ${CHESTNUT_TEST_COMMON_SOURCES}
)

target_include_directories(ChestnutGameEngine_Test PRIVATE
    ${CHESTNUT_LIB_INCLUDE_DIR}
    ${CHESTNUT_TEST_COMMON_INCLUDE_DIR}
)