FIND_PACKAGE(CUDA REQUIRED)
include_directories(../include)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

CUDA_ADD_EXECUTABLE(main main.cpp square.cu)
