INCLUDE_DIRECTORIES(../../include/include_cxx)

FIND_PACKAGE(OpenCV 2.4.9.1 REQUIRED)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/lib_cxx)

SET(HEADERS_CXX 
	../../include/include_cxx/image_io.h
	../../include/include_cxx/define.h)
SET(SOURCE_FILES_CXX 
	image_io.cpp)

ADD_LIBRARY(image_io SHARED ${HEADERS_CXX} ${SOURCE_FILES_CXX})
TARGET_LINK_LIBRARIES(image_io ${OpenCV_LIBS})