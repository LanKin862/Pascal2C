# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ClionCode/Pascal2C/cmake-build-debug/antlr4_runtime/src/antlr4_runtime"
  "D:/ClionCode/Pascal2C/cmake-build-debug/antlr4_runtime/src/antlr4_runtime-build"
  "D:/ClionCode/Pascal2C/cmake-build-debug/antlr4_runtime"
  "D:/ClionCode/Pascal2C/cmake-build-debug/antlr4_runtime/tmp"
  "D:/ClionCode/Pascal2C/cmake-build-debug/antlr4_runtime/src/antlr4_runtime-stamp"
  "D:/ClionCode/Pascal2C/cmake-build-debug"
  "D:/ClionCode/Pascal2C/cmake-build-debug/antlr4_runtime/src/antlr4_runtime-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/ClionCode/Pascal2C/cmake-build-debug/antlr4_runtime/src/antlr4_runtime-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/ClionCode/Pascal2C/cmake-build-debug/antlr4_runtime/src/antlr4_runtime-stamp${cfgdir}") # cfgdir has leading slash
endif()
