include(CTest)
include(Catch)

set(CHESTNUT_TEST_COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/common/test_utils.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/common/test_main.cpp
)
set(CHESTNUT_TEST_COMMON_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

if(CHESTNUT_BUILD_ENGINE)
    add_subdirectory(engine)
endif()

if(CHESTNUT_BUILD_ENGINE_EXTENSIONS)
    add_subdirectory(engine_extensions/graphics3d)
endif()

