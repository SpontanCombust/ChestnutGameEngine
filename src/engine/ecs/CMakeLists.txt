target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/components/kinematics_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/timer_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/transform_component.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/kinematics_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/sdl_event_dispatch_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/timer_system.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system.cpp
)