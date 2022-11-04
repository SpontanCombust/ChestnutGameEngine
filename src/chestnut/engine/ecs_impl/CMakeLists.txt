target_sources(${PROJECT_NAME} PRIVATE   
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener_guard.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener_guard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system.cpp
)

include_directories(components)
include_directories(events)
include_directories(systems)