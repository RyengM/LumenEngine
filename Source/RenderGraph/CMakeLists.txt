cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME RenderGraph)
project(${PROJECT_NAME})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB HEADER_FILES "*.h")
file(GLOB SOURCE_FILES "*.cpp")

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin/$(Configuration)")