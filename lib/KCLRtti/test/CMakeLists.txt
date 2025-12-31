cmake_minimum_required(VERSION 3.1.0)

project(${PARENT_PROJECT_NAME}_test)

include(CTest)
enable_testing()

add_executable(${PARENT_PROJECT_NAME}_test ${PARENT_PROJECT_NAME}_test.cpp)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

target_include_directories(${PARENT_PROJECT_NAME}_test PRIVATE
    ${PARENT_PROJECT_NAME}/include
    ${CMAKE_SOURCE_DIR}/utils
)

target_link_libraries(${PARENT_PROJECT_NAME}_test ${PARENT_PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

gtest_discover_tests(${PARENT_PROJECT_NAME}_test)

