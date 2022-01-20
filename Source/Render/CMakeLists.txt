cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Render)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")

file(GLOB RENDER_GRAPH_FILES "RenderGraph/Public/*.h" "RenderGraph/Private/*.cpp")
file(GLOB RENDER_CORE_FILES "RenderCore/Public/*.h" "RenderCore/Private/*.cpp")
file(GLOB RENDER_PROXY_FILES "RenderProxy/Public/*.h" "RenderProxy/Private/*.cpp")
file(GLOB RHI_COMMON_FILES "RHI/Common/Public/*.h" "RHI/Common/Private/*.cpp")
file(GLOB RHI_D3D12_FILES  "RHI/D3D12/Public/*.h" "RHI/D3D12/Private/*.cpp")
source_group("RenderGraph" FILES ${RENDER_GRAPH_FILES})
source_group("RenderCore" FILES ${RENDER_CORE_FILES})
source_group("RenderProxy" FILES ${RENDER_PROXY_FILES})
source_group("RHI\\Common" FILES ${RHI_COMMON_FILES})
source_group("RHI\\D3D12" FILES ${RHI_D3D12_FILES})

add_library(${PROJECT_NAME} ${RENDER_GRAPH_FILES} ${RENDER_CORE_FILES} ${RENDER_PROXY_FILES} ${RHI_COMMON_FILES} ${RHI_D3D12_FILES})

add_dependencies (${PROJECT_NAME} Core)

target_link_libraries(${PROJECT_NAME} 
	debug ${CMAKE_SOURCE_DIR}/Lib/Core_d.lib
	optimized ${CMAKE_SOURCE_DIR}/Lib/Core.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()