target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/timers/auto_timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timers/locked_auto_timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timers/locked_manual_timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timers/manual_timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/timers/timer.cpp
)
