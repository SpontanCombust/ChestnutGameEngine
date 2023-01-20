target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_graphics.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_graphics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_math.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_math.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_misc.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_misc.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_physics.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_physics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_resources.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/serializers_resources.cpp
)

add_subdirectory(serializers_ecs_impl)