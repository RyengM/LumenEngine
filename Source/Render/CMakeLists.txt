cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Render)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")

file(GLOB RENDER_GRAPH_FILES "RenderGraph/Public/*.h" "RenderGraph/Private/*.cpp")
file(GLOB RENDER_CORE_FILES "RenderCore/Public/*.h" "RenderCore/Private/*.cpp")
file(GLOB RHI_FILES "RHI/Public/*.h" "RHI/Private/*.cpp")
source_group("RenderGraph" FILES ${RENDER_GRAPH_FILES})
source_group("RenderCore" FILES ${RENDER_CORE_FILES})
source_group("RHI" FILES ${RHI_FILES})

add_library(${PROJECT_NAME} ${RENDER_GRAPH_FILES} ${RENDER_CORE_FILES} ${RHI_FILES})

add_dependencies (${PROJECT_NAME} Core)

target_link_libraries(${PROJECT_NAME} 
	debug ${CMAKE_SOURCE_DIR}/Lib/Core_d.lib
	optimized ${CMAKE_SOURCE_DIR}/Lib/Core.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")