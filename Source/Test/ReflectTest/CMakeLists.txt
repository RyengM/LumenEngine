cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME ReflectTest)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty")

file(GLOB_RECURSE SOURCE_FILES "*.h" "*.inl" "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_dependencies (${PROJECT_NAME} RTTR Game)

target_link_libraries(${PROJECT_NAME}
    debug ${CMAKE_SOURCE_DIR}/Lib/Game_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/RTTR_d.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Game.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/RTTR.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Test")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin/Test)