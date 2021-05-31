cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME RenderGraph)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Include")

file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}/Include/RenderGraph/*.h")
file(GLOB SOURCE_FILES "*.cpp")

add_library(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")