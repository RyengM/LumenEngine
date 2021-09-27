cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX _d)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(PROJECT_NAME LumenEngine)
project(${PROJECT_NAME} LANGUAGES CXX)

add_subdirectory(Source/Core)
add_subdirectory(Source/Render)
add_subdirectory(Source/Game)
add_subdirectory(Source/App)
add_subdirectory(Source/ThirdParty)
add_subdirectory(Source/Test)