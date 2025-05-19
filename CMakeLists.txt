cmake_minimum_required(VERSION 3.20)
project(Pascal2C)

option(BUILD_TESTING "Build tests" OFF)

set(CMAKE_CXX_STANDARD 11)

# glob all source files under src/ recursively
file(GLOB_RECURSE SOURCES "src/*.cpp" "antlr/*.cpp")

IF(UNIX)
    # Find the ANTLR4 library installed in the system
    find_library(ANTLR4_RUNTIME_LIB antlr4-runtime PATHS /usr/local/lib NO_DEFAULT_PATH)
    if(NOT ANTLR4_RUNTIME_LIB)
        message(FATAL_ERROR "ANTLR4 runtime library not found in /usr/local/lib")
    endif()

    # Find ANTLR4 include directories
    find_path(ANTLR4_INCLUDE_DIR antlr4-runtime.h PATHS /usr/local/include/antlr4-runtime)
    if(NOT ANTLR4_INCLUDE_DIR)
        message(FATAL_ERROR "ANTLR4 include directory not found")
    endif()

    include_directories(${ANTLR4_INCLUDE_DIR})

    # 检查SOURCES变量是否为空
    if(NOT SOURCES)
        message(FATAL_ERROR "No source files found! Please check your source directories.")
    endif()

    add_executable(pascc ${SOURCES})
    target_link_libraries(pascc ${ANTLR4_RUNTIME_LIB})

    add_custom_command(TARGET pascc
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/../bin
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pascc> ${CMAKE_SOURCE_DIR}/../bin/
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
ENDIF (UNIX)

IF(WIN32)
    add_definitions(-DANTLR4CPP_STATIC)

    set(ANTLR4_WITH_STATIC_CRT OFF)

    include(cmake/ExternalAntlr4Cpp.cmake)

    include_directories(${ANTLR4_INCLUDE_DIRS})
    if(NOT SOURCES)
        message(FATAL_ERROR "No source files found! Please check your source directories.")
    endif()

    add_executable(pascc ${SOURCES})

    target_link_libraries(pascc antlr4_shared)
    add_custom_command(TARGET pascc
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/../bin
            COMMAND ${CMAKE_COMMAND} -E copy ${ANTLR4_RUNTIME_LIBRARIES} ${CMAKE_SOURCE_DIR}/../bin/
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pascc> ${CMAKE_SOURCE_DIR}/../bin/
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
ENDIF (WIN32)