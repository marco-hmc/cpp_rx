project(rtti_benchmark)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/utils)
add_executable(${PROJECT_NAME} ${SOURCES})

# ADD_MODULE(${PROJECT_NAME} dynamicCast KCLRtti Rtti)
ADD_LIB_MODULE(${PROJECT_NAME} dynamicCast Rtti KCLRtti)