include_directories(../include/include_cuda)
include_directories(../include/include_cxx)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(main main.cpp)
target_link_libraries(main rgb2gray image_io)
