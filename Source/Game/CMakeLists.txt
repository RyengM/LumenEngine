cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Game)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")

file(GLOB GAMEPLAY_FILES "GamePlay/Public/*.h" "GamePlay/Private/*.cpp")
file(GLOB WINDOWS_FILES "PlatFormFramework/Windows/Public/*.h" "PlatFormFramework/Windows/Private/*.cpp")
file(GLOB LAUNCH_FILES "Launch/Public/*.h" "Launch/Private/*.cpp")
source_group("GamePlay" FILES ${GAMEPLAY_FILES})
source_group("PlatFormFramework/Windows" FILES ${WINDOWS_FILES})
source_group("Launch" FILES ${LAUNCH_FILES})

add_library(${PROJECT_NAME} ${GAMEPLAY_FILES} ${WINDOWS_FILES} ${LAUNCH_FILES})

add_dependencies (${PROJECT_NAME} Core)

target_link_libraries(${PROJECT_NAME}
    debug ${CMAKE_SOURCE_DIR}/Lib/Core_d.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Core.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")