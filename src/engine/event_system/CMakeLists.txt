target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/event_helpers/event_constraint_functor_creators.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_helpers/registers_keyboard_listeners.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_listener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/event_manager.cpp
)