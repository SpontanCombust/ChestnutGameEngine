set(COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/system_test_utils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system_test_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_utils.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
)

target_sources(${PROJECT_NAME}_Test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/audio_manager_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/colored_polygon2d_renderer_test.cpp
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
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_animation_system_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_rendering_system_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite_renderer_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text_renderer_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timer_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window_test.cpp
    ${COMMON_SOURCES}
)

target_sources(${PROJECT_NAME}_Graphics3D_Test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/camera3d_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/extrude_profile_test.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/phong_renderer_test.cpp
    ${COMMON_SOURCES}
)