cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Render)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")

file(GLOB RENDER_GRAPH_FILES "RenderGraph/Public/*.h" "RenderGraph/Private/*.cpp")
source_group("RenderGraph" FILES ${RENDER_GRAPH_FILES})

add_library(${PROJECT_NAME} ${RENDER_GRAPH_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")