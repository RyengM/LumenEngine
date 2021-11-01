cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME ReflectTest)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/UANTLR")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/UANTLR/Runtime/Public")
include_directories("${CMAKE_SOURCE_DIR}/Source/Tools/USRefl_AutoRefl/Public")

file(GLOB SOURCE_FILES "*.h" "*.inl" "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Test")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin/Test)