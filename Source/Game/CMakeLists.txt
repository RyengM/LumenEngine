cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME Game)
project(${PROJECT_NAME})

include_directories("${CMAKE_SOURCE_DIR}/Source")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Spdlog/include")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/ANTLR/Runtime/Public")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty")
include_directories("${CMAKE_SOURCE_DIR}/Source/ThirdParty/Assimp")

file(GLOB GAMEPLAY_FILES "GamePlay/Public/*.h" "GamePlay/Public/Details/*.inl" "GamePlay/Private/*.cpp")
file(GLOB WINDOWS_FILES "PlatFormFramework/Windows/Public/*.h" "PlatFormFramework/Windows/Private/*.cpp")
file(GLOB ENGINE_FILES "Engine/Public/*.h" "Engine/Private/*.cpp")
file(GLOB ASSET_FILES "Asset/Public/*.h" "Asset/Public/Details/*.inl" "Asset/Private/*.cpp")
source_group("GamePlay" FILES ${GAMEPLAY_FILES})
source_group("PlatFormFramework/Windows" FILES ${WINDOWS_FILES})
source_group("Engine" FILES ${ENGINE_FILES})
source_group("Asset" FILES ${ASSET_FILES})

add_library(${PROJECT_NAME} ${GAMEPLAY_FILES} ${WINDOWS_FILES} ${ENGINE_FILES} ${ASSET_FILES})

add_dependencies (${PROJECT_NAME} Core Render RTTR Imgui ANTLR_Runtime ANTLR_ParserShaderLab)

target_link_libraries(${PROJECT_NAME}
    debug ${CMAKE_SOURCE_DIR}/Lib/Core_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/Render_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/RTTR_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/Imgui_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/ANTLR_Runtime_d.lib
    debug ${CMAKE_SOURCE_DIR}/Lib/ANTLR_ParserShaderLab_d.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Core.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Render.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/RTTR.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/Imgui.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/ANTLR_Runtime.lib
    optimized ${CMAKE_SOURCE_DIR}/Lib/ANTLR_ParserShaderLab.lib
    Assimp)

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")

add_definitions(-DANTLR4CPP_STATIC)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MP")
endif()

ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/Assimp/assimp-vc142-mt.dll ${CMAKE_SOURCE_DIR}/Bin/$(Configuration))
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/Assimp/Library ${CMAKE_SOURCE_DIR}/Lib)