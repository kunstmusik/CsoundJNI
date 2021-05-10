cmake_minimum_required(VERSION 3.11)
project(csoundjni)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "")
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)
set(NATIVE_INSTALL_PATH "${CMAKE_SOURCE_DIR}/src/main/resources/com/kunstmusik/csoundjni/native")

find_package(Java 11 REQUIRED COMPONENTS Development)
find_package(JNI REQUIRED)
find_package(Csound REQUIRED)
include(UseJava)

include_directories(${JNI_INCLUDE_DIRS} ${CSOUND_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES src/main/cpp/CsoundJNI.cpp
  src/main/cpp/com_kunstmusik_csoundjni_CsoundJNI.h)

#set(JAVA_SOURCE_FILES 
#  src/main/java/com/kunstmusik/csoundjni/CsoundJNI.java
#  src/main/java/com/kunstmusik/csoundjni/Csound.java)

#add_jar(CsoundJNI SOURCES ${JAVA_SOURCE_FILES}
#  GENERATE_NATIVE_HEADERS csoundjni-native-headers)

add_library(csoundjni-native SHARED ${SOURCE_FILES})
set_target_properties(csoundjni-native PROPERTIES OUTPUT_NAME csoundjni)
target_link_libraries(csoundjni-native PRIVATE ${CSOUND_LIBRARY})
install(TARGETS csoundjni-native DESTINATION ${NATIVE_INSTALL_PATH})

if(APPLE)
  set_target_properties(csoundjni-native PROPERTIES
    PREFIX "lib" SUFFIX ".jnilib")
endif()
