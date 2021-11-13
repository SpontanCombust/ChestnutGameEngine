target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/components/collision2d_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/kinematics2d_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/model2d_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/render_layer_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/texture2d_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/timer_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/transform2d_component.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/kinematics2d_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/simple2d_collision_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/simple2d_rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/input_event_dispatch_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/timer_system.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener_guard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system.cpp
)