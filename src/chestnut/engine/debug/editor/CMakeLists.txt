target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gui_editor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui_editor.cpp
)

add_subdirectory(component_views)
