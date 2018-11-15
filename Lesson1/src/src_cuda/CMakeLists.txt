find_package(CUDA REQUIRED)
find_package(OpenCV 2.4.9.1 REQUIRED)

include_directories(../../include/include_cuda)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/lib_cuda)

set(HEADERS_CUDA
	../../include/include_cuda/rgb2gray.cuh
)

set(SOURCE_FILES_CUDA 
	rgb2gray.cu
)

cuda_add_library(rgb2gray SHARED ${HEADERS_CUDA} ${SOURCE_FILES_CUDA})
target_link_libraries(rgb2gray ${OpenCV_LIBS})
