target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/component_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/kinematics_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/sdl_event_dispatch_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/timer_system.cpp
)