cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME SerializeTest)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")

file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_dependencies (${PROJECT_NAME} Core Game RTTR CrossGuid)

target_link_libraries(${PROJECT_NAME}
    debug ${CMAKE_SOURCE_DIR}/Lib/Core_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/Game_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/RTTR_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/CrossGuid_d.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Core.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Game.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/RTTR.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/CrossGuid.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Test")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin/Test)