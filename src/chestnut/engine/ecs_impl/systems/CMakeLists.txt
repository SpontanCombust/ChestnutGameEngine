target_sources(${PROJECT_NAME} PRIVATE   
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/input_event_dispatch_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/input_event_dispatch_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/kinematics2d_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/kinematics2d_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/simple2d_animation_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/simple2d_animation_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/simple2d_collision_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/simple2d_collision_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/simple2d_rendering_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/simple2d_rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/timer_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/timer_system.cpp
)