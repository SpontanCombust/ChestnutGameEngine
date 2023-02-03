target_sources(ChestnutGameEngine PRIVATE   
    ${CMAKE_CURRENT_SOURCE_DIR}/animation2d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera2d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/camera2d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/colored_polygon2d.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/colored_polygon2d.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.cpp
)

add_subdirectory(opengl)
add_subdirectory(renderers)