cmake_minimum_required(VERSION 3.12)
project(Playground)
message(STATUS "start running cmake")

set(CMAKE_CXX_STANDARD 14)

find_library(LIB_GLOG glog)
if(NOT LIB_GLOG)
    message(FATAL_ERROR "libglog not found")
else()
    message(STATUS "LIB_GLOG location ${LIB_GLOG}")
endif()

find_library(LIB_FOLLY folly)
if(NOT LIB_FOLLY)
    message(FATAL_ERROR "libfolly not found")
else()
    message(STATUS "LIB_FOLLY location ${LIB_FOLLY}")
endif()


add_executable(Playground main.cpp)
target_link_libraries(Playground ${LIB_GLOG} ${LIB_FOLLY})