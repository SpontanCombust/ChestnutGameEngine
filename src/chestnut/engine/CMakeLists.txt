add_library(ChestnutGameEngine SHARED)

target_include_directories(ChestnutGameEngine PUBLIC 
    ${CHESTNUT_LIB_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(ChestnutGameEngine PUBLIC
    ${OPENGL_LIBRARIES}
    glad
    chestnut-ecs
    SDL2
    SDL2_ttf
    SDL2_mixer
    optional
    expected
    stb_image
    imgui
    nativefiledialog
    nlohmann_json
)

target_compile_options(ChestnutGameEngine PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_MSVC}>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${CHESTNUT_ENGINE_COMPILE_OPTIONS_GNU}>
)



target_sources(ChestnutGameEngine PRIVATE
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
add_subdirectory(misc)
add_subdirectory(physics)
add_subdirectory(resources)
add_subdirectory(serialization)