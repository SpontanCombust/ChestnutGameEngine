target_sources(${PROJECT_NAME} PRIVATE   
    ${CMAKE_CURRENT_SOURCE_DIR}/debug_gui_rendering_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/debug_gui_rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/garbage_collector_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/garbage_collector_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/input_event_dispatch_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/input_event_dispatch_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/kinematics2d_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/kinematics2d_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_animation_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_animation_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_collision_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_collision_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_rendering_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simple2d_rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timer_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timer_system.cpp
)