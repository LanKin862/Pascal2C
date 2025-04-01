cmake_minimum_required(VERSION 3.25)
project(Pascal2C)

option(BUILD_TESTING "Build tests" OFF)

# ANTLR4 Configuration
##########################################################################
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 11
set(CMAKE_CXX_STANDARD 11)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)

# Specify the version of the antlr4 library needed for this project.
# By default the latest version of antlr4 will be used.  You can specify a
# specific, stable version by setting a repository tag value or a link
# to a zip file containing the libary source.
# set(ANTLR4_TAG 4.13.1)
# set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/4.13.1.zip)

# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
# set(ANTLR_EXECUTABLE /home/user/antlr-4.13.1-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
# find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
# antlr_target(SampleGrammarLexer TLexer.g4 LEXER
#              PACKAGE antlrcpptest)
# antlr_target(SampleGrammarParser TParser.g4 PARSER
#              PACKAGE antlrcpptest
#              DEPENDS_ANTLR SampleGrammarLexer
#              COMPILE_FLAGS -lib ${ANTLR_SampleGrammarLexer_OUTPUT_DIR})

# include generated files in project environment
# include_directories(${ANTLR_SampleGrammarLexer_OUTPUT_DIR})
# include_directories(${ANTLR_SampleGrammarParser_OUTPUT_DIR})

# add generated grammar to demo binary target
# add_executable(demo main.cpp
#                ${ANTLR_SampleGrammarLexer_CXX_OUTPUTS}
#                ${ANTLR_SampleGrammarParser_CXX_OUTPUTS})
# target_link_libraries(demo antlr4_static)
##########################################################################

# glob all source files under src/ recursively
file(GLOB_RECURSE SOURCES "src/*.cpp" "antlr/*.cpp")

# 检查SOURCES变量是否为空
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found! Please check your source directories.")
endif()

add_executable(pascc ${SOURCES})
# target_include_directories(compiler PRIVATE include/ antlr/)
target_link_libraries(pascc ${CMAKE_BINARY_DIR}/antlr4_runtime/src/antlr4_runtime/runtime/Cpp/dist/libantlr4-runtime.so) # for linux only
#target_link_libraries(pascc antlr4_shared)         # for windows only

# Define the correct path to the runtime library
set(ANTLR4_LIB_PATH ${CMAKE_BINARY_DIR}/antlr4_runtime/src/antlr4_runtime/runtime/Cpp/dist/libantlr4-runtime.so) #/this is for linux only/

add_custom_command(TARGET pascc
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/../bin
        COMMAND ${CMAKE_COMMAND} -E copy ${ANTLR4_LIB_PATH} ${CMAKE_SOURCE_DIR}/../bin/   # for linux only
        #        COMMAND ${CMAKE_COMMAND} -E copy ${ANTLR4_RUNTIME_LIBRARIES} ${CMAKE_SOURCE_DIR}/../bin/  # for windows only
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pascc> ${CMAKE_SOURCE_DIR}/../bin/
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})


# # Define a function to abstract the process of adding test targets
# function(add_olc_test_target target_name source_file)
#     file(GLOB_RECURSE LIB_IR_SOURCES "src/ir/*.cpp")
#     add_executable(${target_name} ${source_file} ${LIB_IR_SOURCES})
#     target_include_directories(${target_name} PRIVATE include/ antlr/)
#     target_link_libraries(${target_name} antlr4_shared)
# endfunction()

# # Usage of the newly defined function
# add_olc_test_target(test_ir_asm test/test_ir_asm.cpp)
# add_olc_test_target(test_ir_type test/test_ir_type.cpp)

