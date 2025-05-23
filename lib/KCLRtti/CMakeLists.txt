cmake_minimum_required(VERSION 3.1.0)

project(KCLRtti)

file(GLOB LIB_SOURCES "src/*.cpp")
include_directories("include")
include_directories(${CMAKE_SOURCE_DIR}/utils)
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

set(PARENT_PROJECT_NAME ${PROJECT_NAME})
add_subdirectory(test)
