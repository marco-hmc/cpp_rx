cmake_minimum_required(VERSION 3.1.0)

project(${PARENT_PROJECT_NAME}_test)

include(CTest)
enable_testing()

add_executable(${PARENT_PROJECT_NAME}_test ${PARENT_PROJECT_NAME}_test.cpp)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PARENT_PROJECT_NAME}/include)

target_link_libraries(${PARENT_PROJECT_NAME}_test ${PARENT_PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

gtest_discover_tests(${PARENT_PROJECT_NAME}_test)

