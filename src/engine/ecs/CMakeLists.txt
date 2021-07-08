target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/components/kinematics_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/texture_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/timer_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/components/transform_component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/management/component_batch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/management/component_set_signature.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/management/component_set.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/management/component_storage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/management/entity_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/management/entity_registry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/kinematics_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/rendering_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/sdl_event_dispatch_system.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/systems/timer_system.cpp
)