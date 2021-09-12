cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Core)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")

#file(GLOB ASYNC_FILES "Async/Public/*.h" "Async/Private/*.cpp")
file(GLOB LOGGER_FILES "Logger/Public/*.h" "Logger/Private/*.cpp")
#source_group("Async" FILES ${ASYNC_FILES})
source_group("Logger" FILES ${LOGGER_FILES})

add_library(${PROJECT_NAME} ${LOGGER_FILES})

target_link_libraries(${PROJECT_NAME} 
	debug ${CMAKE_SOURCE_DIR}/Lib/spdlog_d.lib
	optimized ${CMAKE_SOURCE_DIR}/Lib/spdlog.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")