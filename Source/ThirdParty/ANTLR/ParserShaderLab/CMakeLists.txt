cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME ANTLR_ParserShaderLab)
project(${PROJECT_NAME})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Runtime/Public")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Public")

file(GLOB PARSER_FILES "ANTLRShaderLab/*.h" "ANTLRShaderLab/*.cpp")

add_library(${PROJECT_NAME} ${PARSER_FILES})

add_dependencies (${PROJECT_NAME} ANTLR_Runtime)

target_link_libraries(${PROJECT_NAME} 
	debug ${CMAKE_SOURCE_DIR}/Lib/ANTLR_Runtime_d.lib
	optimized ${CMAKE_SOURCE_DIR}/Lib/ANTLR_Runtime.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "ThirdParty")

add_definitions(-DANTLR4CPP_STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()