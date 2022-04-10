cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Imgui)
project(${PROJECT_NAME})

file(GLOB SOURCE_FILES "*.h" "*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "ThirdParty")

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()