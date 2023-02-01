target_sources(ChestnutGameEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/component_rtti.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/component_rtti.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/component_rtti.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
)

add_subdirectory(ecs_lifetime)
add_subdirectory(editor)