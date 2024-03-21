cmake_minimum_required(VERSION 3.10)

project(abc-analyzer CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(abc-analyzer ${SRC_FILES})

target_include_directories(abc-analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)