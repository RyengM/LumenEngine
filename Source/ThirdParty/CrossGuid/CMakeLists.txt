cmake_minimum_required(VERSION 3.5.1)

set(PROJECT_NAME CrossGuid)
project(${PROJECT_NAME} VERSION 0.2.3)

include_directories("${CMAKE_SOURCE_DIR}/Source")

file(GLOB HEADER_FILES "Public/*.hpp")
file(GLOB SOURCE_FILES "Private/*.cpp")

add_library(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GUID_WINDOWS)
elseif(APPLE)
    find_library(CFLIB CoreFoundation)
    target_link_libraries(${PROJECT_NAME} ${CFLIB})
    target_compile_definitions(${PROJECT_NAME} PRIVATE GUID_CFUUID)
elseif(ANDROID)
    # GUID_ANDROID is used in the headers, so make PUBLIC
    target_compile_definitions(${PROJECT_NAME} PUBLIC GUID_ANDROID)
else()
    find_package(Libuuid REQUIRED)
    if (NOT LIBUUID_FOUND)
        message(FATAL_ERROR
            "You might need to run 'sudo apt-get install uuid-dev' or similar")
    endif()
    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBUUID_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${LIBUUID_LIBRARY})
    target_compile_definitions(${PROJECT_NAME} PRIVATE GUID_LIBUUID)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(WARNINGS "-Werror" "-Wall")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(WARNINGS "-Werror" "-Wall")
elseif(MSVC)
    set(WARNINGS "/WX" "/W4")
endif()
target_compile_options(${PROJECT_NAME} PRIVATE ${WARNINGS})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Lib"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Lib")

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "ThirdParty")