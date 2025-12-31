cmake_minimum_required(VERSION 3.15.0)

project(dynamicCast)

file(GLOB LIB_SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

set(PARENT_PROJECT_NAME ${PROJECT_NAME})
# add_subdirectory(test)
