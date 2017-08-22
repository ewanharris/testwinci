# Titanium Windows Native Module - testwinci
#
# Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

cmake_minimum_required(VERSION 3.0.0)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows10")
  set(PLATFORM win10)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsPhone")
  set(PLATFORM phone)
  add_definitions("-DPHONE")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
  set(PLATFORM store)
else()
  message(FATAL_ERROR "This app supports Store / Phone only.")
endif()

project(ComTest)

set(ComTest_VERSION 0.1.0)

set(WINDOWS_SOURCE_DIR "C:/ProgramData/Titanium/mobilesdk/win32/6.2.0.v20170821203442/windows")

SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(ComTest_ARCH "x86")
if(CMAKE_GENERATOR MATCHES "^Visual Studio .+ ARM$")
  set(ComTest_ARCH "ARM")
endif()

option(ComTest_DISABLE_TESTS "Disable compiling the tests" OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(APPCELERATOR_CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ABSOLUTE)
list(INSERT CMAKE_MODULE_PATH 0 ${APPCELERATOR_CMAKE_MODULE_PATH})

find_package(HAL REQUIRED)
find_package(TitaniumKit REQUIRED)
find_package(TitaniumWindows_Utility REQUIRED)

enable_testing()

set(SOURCE_ComTest
  include/ComTest.hpp
  src/ComTest.cpp
  )

source_group(ComTest FILES ${SOURCE_ComTest})

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(ComTest SHARED
  ${SOURCE_ComTest}
  )

include(GenerateExportHeader)
generate_export_header(ComTest)
target_compile_definitions(ComTest PRIVATE ComTest_EXPORTS)

target_include_directories(ComTest PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:HAL,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumKit,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Utility,INTERFACE_INCLUDE_DIRECTORIES>
  )

file(GLOB MODULE_TARGET_LIBS ${PROJECT_SOURCE_DIR}/lib/${PLATFORM}/${ComTest_ARCH}/*.lib)

target_link_libraries(ComTest
  HAL
  TitaniumKit
  TitaniumWindows_Utility
  ${MODULE_TARGET_LIBS}
  )

set_target_properties(ComTest PROPERTIES VS_WINRT_COMPONENT TRUE)

set_property(TARGET ComTest APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")

if (NOT ComTest_DISABLE_TESTS)
  add_subdirectory(test)
endif()

set_property(TARGET ComTest PROPERTY VERSION ${ComTest_VERSION})
set_property(TARGET ComTest PROPERTY SOVERSION 0)
set_property(TARGET ComTest PROPERTY INTERFACE_ComTest_MAJOR_VERSION 0)
set_property(TARGET ComTest APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING ComTest_MAJOR_VERSION
  )


file(GLOB MODULE_WINRT_REFERENCES ${PROJECT_SOURCE_DIR}/lib/${PLATFORM}/${ComTest_ARCH}/*.winmd)
set_property(TARGET ComTest
  PROPERTY VS_WINRT_REFERENCES
  ${MODULE_WINRT_REFERENCES}
)

install(TARGETS ComTest EXPORT ComTest_Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )

export(EXPORT ComTest_Targets
  FILE "${CMAKE_BINARY_DIR}/ComTest_Targets.cmake"
)

configure_file(cmake/ComTest_Config.cmake
  "${CMAKE_BINARY_DIR}/ComTest_Config.cmake"
  COPYONLY
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/ComTest_ConfigVersion.cmake"
  VERSION ${ComTest_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

export(PACKAGE ComTest)