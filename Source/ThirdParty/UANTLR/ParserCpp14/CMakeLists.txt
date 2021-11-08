cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME UANTLR_ParserCpp14)
project(${PROJECT_NAME})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Runtime/Public")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Public")

file(GLOB PARSER_CPP_FILES "Public/*.h" "Private/*.cpp")

add_library(${PROJECT_NAME} ${PARSER_CPP_FILES})

add_dependencies (${PROJECT_NAME} UANTLR_Runtime)

target_link_libraries(${PROJECT_NAME} 
	debug ${CMAKE_SOURCE_DIR}/Lib/UANTLR_Runtime_d.lib
	optimized ${CMAKE_SOURCE_DIR}/Lib/UANTLR_Runtime.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "ThirdParty")

add_definitions(-DANTLR4CPP_STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")