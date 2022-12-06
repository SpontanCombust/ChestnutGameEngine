target_sources(${PROJECT_NAME}_Graphics3D PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/camera3d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera3d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/light.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/material.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mesh.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mesh.cpp
)

add_subdirectory(algorithms)
add_subdirectory(renderers)