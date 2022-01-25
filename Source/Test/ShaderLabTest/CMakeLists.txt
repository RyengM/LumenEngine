cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME ShaderLabTest)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/ANTLR/Runtime/Public")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")

file(GLOB SOURCE_FILES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_dependencies (${PROJECT_NAME} Game)

target_link_libraries(${PROJECT_NAME} 
    debug ${CMAKE_SOURCE_DIR}/Lib/Game_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/Core_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/RTTR_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/ANTLR_Runtime_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/ANTLR_ParserShaderLab_d.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Game.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Core.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/RTTR.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/ANTLR_Runtime.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/ANTLR_ParserShaderLab.lib)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Test")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Bin/Test)