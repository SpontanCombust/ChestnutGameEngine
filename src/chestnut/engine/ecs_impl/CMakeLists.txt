target_sources(ChestnutGameEngine PRIVATE   
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/logic_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rendering_system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/system.cpp
)

add_subdirectory(components)
add_subdirectory(events)
add_subdirectory(systems)