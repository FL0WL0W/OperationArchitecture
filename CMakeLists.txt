# CMakeList.txt : CMake project for OperationArchitecture, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.30[3.30)
option(OperationArchitecture_build_tests "Build all of OperationArchitecture tests" OFF)

set(TARGET		OperationArchitecture)
set(HDR_DIR		include)
set(SRCS_DIR	src)

project(${TARGET} CXX)

# headers are always in include/
file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS ${HDR_DIR}/*.h)
include_directories(${HDR_DIR})
# sources are always in src/
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS ${SRCS_DIR}/*.cpp)

# create library
add_library(${TARGET} STATIC ${HDRS} ${SRCS})
target_include_directories(${TARGET} PUBLIC ${HDR_DIR})

if(OperationArchitecture_build_tests)
    #include mock
    add_subdirectory (mock)
    # include tests
    add_subdirectory (test)
endif()
