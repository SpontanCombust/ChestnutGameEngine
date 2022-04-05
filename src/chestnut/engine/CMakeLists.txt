target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/constants.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/init.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/init.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/macros.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/types.hpp
)

add_subdirectory(audio)
add_subdirectory(debug)
add_subdirectory(ecs_impl)
add_subdirectory(graphics)
add_subdirectory(main)
add_subdirectory(maths)
add_subdirectory(memory)
add_subdirectory(misc)
add_subdirectory(physics)
add_subdirectory(resources)