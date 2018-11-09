cmake_minimum_required (VERSION 2.8 )
project(usehello)

ADD_EXECUTABLE (usehello usehello.h)
TARGET_LINK_LIBRARIES(usehello hello)
