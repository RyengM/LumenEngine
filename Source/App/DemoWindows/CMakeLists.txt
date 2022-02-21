cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME DemoWin)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source" "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty")

file(GLOB DEMO_FILES "Public/*.h" "Private/*.cpp")
source_group("Demo" FILES ${DEMO_FILES})

add_executable(${PROJECT_NAME} WIN32 ${DEMO_FILES})

add_dependencies (${PROJECT_NAME} Core Game Render)

target_link_libraries(${PROJECT_NAME} 
    debug ${CMAKE_SOURCE_DIR}/Lib/Game_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/Core_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/Render_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/RTTR_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/Imgui_d.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Game.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Core.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Render.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/RTTR.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Imgui.lib )

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "App")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin)