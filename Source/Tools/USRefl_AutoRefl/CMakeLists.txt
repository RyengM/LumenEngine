cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME USRefl)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/ANTLR")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/ANTLR/Runtime/Public")
include_directories("${CMAKE_SOURCE_DIR}/Source/Tools/USRefl_AutoRefl/Public/")

file(GLOB USREFL_FILES "Public/*.h" "Public/USRefl/*.h" "Public/USRefl/detail/*.h" "Public/USRefl/detial/*.inl" "Private/*.cpp")

add_executable(${PROJECT_NAME} ${USREFL_FILES})

add_dependencies (${PROJECT_NAME} ANTLR_ParserCpp14 ANTLR_Runtime)

target_link_libraries(${PROJECT_NAME}
    debug ${CMAKE_SOURCE_DIR}/Lib/ANTLR_ParserCpp14_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/ANTLR_Runtime_d.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/ANTLR_ParserCpp14.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/ANTLR_Runtime.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Tools")

add_definitions(-DANTLR4CPP_STATIC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()