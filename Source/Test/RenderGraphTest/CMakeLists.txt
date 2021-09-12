cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME RenderGraphTest)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")

file(GLOB SOURCE_FILES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} 
	debug ${CMAKE_SOURCE_DIR}/Lib/Render_d.lib
	optimized ${CMAKE_SOURCE_DIR}/Lib/Render.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Test")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin/Test)