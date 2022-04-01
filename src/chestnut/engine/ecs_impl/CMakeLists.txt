target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/components/animation2d_component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/animation2d_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/collision2d_component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/collision2d_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/kinematics2d_component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/kinematics2d_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/model2d_component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/model2d_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/render_layer_component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/render_layer_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/texture2d_component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/texture2d_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/timer_component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/timer_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/transform2d_component.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/transform2d_component.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/events/animation_finish_event.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/events/collision_event.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/events/timer_event.hpp

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

    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener_guard.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener_guard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.tpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system.cpp
)