cmake_minimum_required(VERSION 3.12)
project(CPPPlayground)
message(STATUS "start running cmake")

set(CMAKE_CXX_STANDARD 14)

# Install glog from here
# https://github.com/google/glog/
# clone
# cmake .
# make; make install
# should be installed in /usr/local/lib/
find_library(LIB_GLOG glog)
if(NOT LIB_GLOG)
    message(FATAL_ERROR "libglog not found")
else()
    message(STATUS "LIB_GLOG location ${LIB_GLOG}")
endif()

find_library(LIB_GTEST gtest)
if(NOT LIB_GTEST)
    message(FATAL_ERROR "libgtest not found")
else()
    message(STATUS "LIB_GTEST location ${LIB_GTEST}")
endif()

# brew install folly
# brew ls -v folly
# this should show install location
find_library(LIB_FOLLY folly)
if(NOT LIB_FOLLY)
    message(FATAL_ERROR "libfolly not found")
else()
    message(STATUS "LIB_FOLLY location ${LIB_FOLLY}")
endif()


add_executable(CPPPlayground futures_koans.cpp)

target_link_libraries(CPPPlayground ${LIB_GLOG} ${LIB_FOLLY} ${LIB_GTEST})