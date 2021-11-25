cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Core)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty")

file(GLOB COMMON_FILES "Common/Public/*.h" "Common/Public/*.hpp" "Common/Public/Details/*.inl" "Common/Private/*.cpp")
file(GLOB LOGGER_FILES "Logger/Public/*.h" "Logger/Private/*.cpp")
file(GLOB TASK_GRAPH_FILES "TaskGraph/Public/*.h" "TaskGraph/Public/Details/*.inl" "TaskGraph/Private/*.cpp")
file(GLOB THREAD_FILES "Thread/Public/*.h" "Thread/Public/Details/*.inl" "Thread/Private/*.cpp")
file(GLOB MEMORY_FILES "Memory/Public/*.h" "Memory/Public/Details/*.inl" "Memory/Private/*.cpp")
file(GLOB MATH_FILES "Math/Public/*.h" "Math/Public/Details/*.inl" "Math/Private/*.cpp")
source_group("Common" FILES ${COMMON_FILES})
source_group("Logger" FILES ${LOGGER_FILES})
source_group("TaskGraph" FILES ${TASK_GRAPH_FILES})
source_group("Thread" FILES ${THREAD_FILES})
source_group("Memory" FILES ${MEMORY_FILES})
source_group("Math" FILES ${MATH_FILES})

add_library(${PROJECT_NAME} ${COMMON_FILES} ${LOGGER_FILES} ${TASK_GRAPH_FILES} ${THREAD_FILES} ${MEMORY_FILES} ${MATH_FILES})

add_dependencies (${PROJECT_NAME} spdlog RTTR)

target_link_libraries(${PROJECT_NAME}
    debug ${CMAKE_SOURCE_DIR}/Lib/spdlog_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/RTTR_d.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/spdlog.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/RTTR.lib)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")