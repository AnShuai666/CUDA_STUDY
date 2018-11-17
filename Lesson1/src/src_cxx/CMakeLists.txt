find_package(OpenCV 2.4.9.1 REQUIRED)
include_directories(../../include/include_cxx)
include_directories(${OpenCV_INCLUDE_DIRS})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/lib_cxx)
set(HEADERS_CXX
        ../../include/include_cxx/image_io.h
        ../../include/include_cxx/define.h)
set(SOURCE_FILES_CXX
        image_io.cpp)

add_library(image_io SHARED ${HEADERS_CXX} ${SOURCE_FILES_CXX})
target_link_libraries(image_io ${OpenCV_LIBS})
