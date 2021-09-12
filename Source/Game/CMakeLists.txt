cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Game)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")

file(GLOB GAME_FRAMEWORK_FILES "GameFramework/Public/*.h" "GameFramework/Private/*.cpp")
file(GLOB PLATFORM_FRAMEWORK_FILES "PlatFormFramework/Public/*.h" "PlatFormFramework/Private/*.cpp")
source_group("GameFramework" FILES ${GAME_FRAMEWORK_FILES})
source_group("PlatFormFramework" FILES ${PLATFORM_FRAMEWORK_FILES})

add_library(${PROJECT_NAME} ${GAME_FRAMEWORK_FILES} ${PLATFORM_FRAMEWORK_FILES})

target_link_libraries(${PROJECT_NAME} 
	debug ${CMAKE_SOURCE_DIR}/Lib/Core_d.lib
	optimized ${CMAKE_SOURCE_DIR}/Lib/Core.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")