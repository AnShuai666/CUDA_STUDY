INCLUDE_DIRECTORIES(../include/include_cxx)
INCLUDE_DIRECTORIES(../include/include_cuda)

SET(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main gaussBlur image_io)
