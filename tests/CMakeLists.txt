target_sources(${PROJECT_NAME}_Test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager_test.cpp
    #TODO add tests for matrices
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_2_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_3_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_4_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_cast_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/math_vector_n_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
)