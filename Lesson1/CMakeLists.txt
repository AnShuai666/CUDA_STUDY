CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(Lesson1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fPIC")
set(CMAKE_BUILD_TYPE "Debug")

add_subdirectory(src_bin)
add_subdirectory(src/src_cuda)
add_subdirectory(src/src_cxx)

