# =================================== PREAMBULE ===================================

cmake_minimum_required(VERSION 3.11.0)
project(ChestnutGameEngine VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(MSVC)
    include(GenerateExportHeader)
endif()


# ========================== PROJECT OPTIONS AND VARIABLES ============================

# add debug define
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DCHESTNUT_DEBUG")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCHESTNUT_DEBUG")
endif()


set(CHESTNUT_ENGINE_COMPILE_OPTIONS_GNU     -Wall -Wpedantic -Wno-unused-variable)

# 4100, 4101 - unused variables
# 4251 - x needs to have dll interface
#   This shows up even for private members which just happened to be STL objects
#   You can make the warning go away by exporting individual methods instead of the entire class,
#   but this lib is not intended to be C-compatible, so these warnings should be ignored.
# 4834 - ignored [[nodiscard]] - this comes from tl::typelist
set(CHESTNUT_ENGINE_COMPILE_OPTIONS_MSVC    /W3 /wd4100 /wd4101 /wd4834 /wd4251)

set(CHESTNUT_ENGINE_LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CHESTNUT_ENGINE_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)


if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CHESTNUT_IS_MAIN_PROJECT TRUE)
else()
    set(CHESTNUT_IS_MAIN_PROJECT FALSE)
endif()

option(CHESTNUT_BUILD_ENGINE "Build ChestnutGameEngine library" ON)
option(CHESTNUT_BUILD_ENGINE_EXTENSIONS "Build ChestnutGameEngine extension libraries" OFF)
option(CHESTNUT_BUILD_ENGINE_EDITOR "Build ChestnutGameEngineEditor" ON)
option(CHESTNUT_BUILD_TESTS "Build ChestnutGameEngine project tests" ${CHESTNUT_IS_MAIN_PROJECT})



# =============================== DEPENDENCIES & UTILS ================================

include(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Dependencies.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/Utilities.cmake)



# ====================================== TARGETS ======================================


# ChestnutGameEngine
if(CHESTNUT_BUILD_ENGINE)
    add_subdirectory(src/chestnut/engine)
endif()


# ChestnutGameEngine_Graphics3D
if(CHESTNUT_BUILD_ENGINE_EXTENSIONS)
    add_subdirectory(src/chestnut/engine_extensions/graphics3d)
endif()


# ChestnutGameEngine
if(CHESTNUT_BUILD_ENGINE_EDITOR)
    add_subdirectory(src/chestnut/engine_editor)
endif()


# ChestnutGameEngine_Test, ChestnutGameEngine_Graphics3D_Test
if(CHESTNUT_BUILD_TESTS)
    add_subdirectory(tests)
endif()