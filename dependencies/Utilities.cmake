macro(copy_shared_libs)
    set(prefix P)
    set(options OPTION)
    set(singleValues TARGET)
    set(multiValues DEPENDENCIES)

    include(CMakeParseArguments)
    cmake_parse_arguments(
        "${prefix}"
        "${options}"
        "${singleValues}"
        "${multiValues}"
        "${ARGN}"
    )

    foreach(D IN ITEMS ${P_DEPENDENCIES})
        add_custom_command(TARGET ${P_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${D}>  $<TARGET_FILE_DIR:${P_TARGET}>
        )
    endforeach()
    
endmacro()