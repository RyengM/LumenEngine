cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME ANTLR_Runtime)
project(${PROJECT_NAME})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Public")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Public/atn")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Public/dfa")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Public/misc")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Public/support")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Public/tree")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Public/tree/xpath")

file(GLOB RUNTIME_FILES "Public/*.h" "Public/atn/*.h" "Public/dfa/*.h" "Public/misc/*.h" "Public/support/*.h" "Public/tree/*.h" "Public/tree/pattern/*.h" "Public/tree/xpath/*.h"
                        "Private/*.cpp" "Private/atn/*.cpp" "Private/dfa/*.cpp" "Private/misc/*.cpp" "Private/support/*.cpp" "Private/tree/*.cpp" "Private/tree/pattern/*.cpp" "Private/tree/xpath/*.cpp")

add_library(${PROJECT_NAME} ${RUNTIME_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "ThirdParty")

add_definitions(-DANTLR4CPP_STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()