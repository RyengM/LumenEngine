cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME ParserTest)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/UANTLR/Runtime/Public")

file(GLOB SOURCE_FILES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_dependencies (${PROJECT_NAME} UANTLR_ParserCpp14 UANTLR_Runtime)

target_link_libraries(${PROJECT_NAME}
	debug ${CMAKE_SOURCE_DIR}/Lib/UANTLR_ParserCpp14_d.lib
	debug ${CMAKE_SOURCE_DIR}/Lib/UANTLR_Runtime_d.lib
	optimized ${CMAKE_SOURCE_DIR}/Lib/UANTLR_ParserCpp14.lib
	optimized ${CMAKE_SOURCE_DIR}/Lib/UANTLR_Runtime.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Test")

add_definitions(-DANTLR4CPP_STATIC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin/Test)