target_sources(${PROJECT_NAME}_Test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager_test.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/math_matrix_3_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_matrix_4_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_matrix_n_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_2_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_3_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_4_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_cast_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_n_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_transform_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite_renderer_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timer_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
)