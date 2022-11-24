cmake_minimum_required(VERSION 3.18)
include(CMakeDependentOption)
project("calango" LANGUAGES CXX)

# General compiler settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Valid platforms
set(PLATFORM win64 CACHE STRING "Target platform" FORCE)
set_property(CACHE PLATFORM PROPERTY STRINGS win64)

if (MSVC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  add_compile_options(/W3 /WX)
endif()

set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

# Directory output files single config generators
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/calangoSDK/lib 
  CACHE PATH "Output directory for static libraries.")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/calangoSDK/lib
  CACHE PATH "Output directory for shared libraries.")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/calangoSDK/bin
  CACHE PATH "Output directory for executables and DLL's.")

# Directory output files for multi config generators
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/calangoSDK/bin" CACHE PATH "" FORCE)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/calangoSDK/lib" CACHE PATH "" FORCE)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_BINARY_DIR}/calangoSDK/lib" CACHE PATH "" FORCE)
endforeach()

#
# calango_platform.dll: OS dependent code implementation of the platform layer
#
add_library(calango_platform SHARED
  "${SOURCE_PATH}/${PLATFORM}/calango_platform_${PLATFORM}.cpp"
  ${SOURCE_PATH}/include/calango/calango_platform.h)
target_include_directories(calango_platform PUBLIC "${SOURCE_PATH}/include")
target_compile_options(calango_platform PRIVATE -DCALANGO_PLATFORM_IMPLEMENTATION)


#
# Add windows resource files only if we are building for windows
#
if("${PLATFORM}" STREQUAL win64)
  set(calango_WINDOWS_RESOURCE_FILE "${SOURCE_PATH}/win64/calango_resource_win64.rc")
endif()

#
# calango.dll: calango engine itself
#
add_library(calango SHARED ${SOURCE_PATH}/calango_engine.cpp 
  ${SOURCE_PATH}/include/calango/calango_engine.h
  ${SOURCE_PATH}/include/calango/calango.h
  "${calango_WINDOWS_RESOURCE_FILE}")
target_include_directories(calango PUBLIC "${SOURCE_PATH}/include")
target_compile_options(calango PRIVATE -DCALANGO_ENGINE_IMPLEMENTATION)
target_link_libraries(calango PRIVATE calango_platform)
add_custom_command(TARGET calango POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/calangoSDK/include
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_PATH}/include/calango/ ${CMAKE_BINARY_DIR}/calangoSDK/include)

#
# clauncher.exe: Editor / Game launcher
#
add_executable(clauncher WIN32 ${SOURCE_PATH}/calango_launcher.cpp "${calango_WINDOWS_RESOURCE_FILE}")
target_link_libraries(clauncher PRIVATE calango calango_platform)


