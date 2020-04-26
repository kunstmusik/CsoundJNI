cmake_minimum_required(VERSION 2.8)
project(jcsound)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_BUILD_TYPE Release)

find_package(JNI REQUIRED)
find_package(CSOUND REQUIRED)

include_directories(${JNI_INCLUDE_DIRS} ${CSOUND_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/JCsound.cpp)

add_library(jcsound SHARED ${SOURCE_FILES})
target_link_libraries(jcsound ${CSOUND_LIBRARY})
