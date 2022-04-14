add_subdirectory(opengl)

target_sources(${PROJECT_NAME} PRIVATE   
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/colored_polygon2d_renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/colored_polygon2d_renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/phong_renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/phong_renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/plain_mesh_renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/plain_mesh_renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/sprite_renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/sprite_renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/text_renderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renderers/text_renderer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/animation2d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/animation2d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera2d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera2d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera3d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera3d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/colored_polygon2d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/colored_polygon2d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/extrude_profile.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/extrude_profile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/light.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/light.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/material.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mesh.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.cpp
)