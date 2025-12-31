cmake_minimum_required(VERSION 3.15.0)

project(MyProjce)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(CTest)
enable_testing()

include(${CMAKE_SOURCE_DIR}/cmake/linkDll.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/TargetGroups.cmake)

find_package(spdlog CONFIG REQUIRED)

# 设置全局输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

add_subdirectory(benchmark)

# ----- build lib && dll ----- #
add_subdirectories("lib")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
target_group_all()