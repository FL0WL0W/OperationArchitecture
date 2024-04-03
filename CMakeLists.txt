# CMakeList.txt : CMake project for OperationArchitecture, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
option(OperationArchitecture_build_tests "Build all of OperationArchitecture tests" OFF)

set(TARGET		OperationArchitecture)

project(${TARGET} CXX)

# headers are always in include/
set(HDR_DIR		include)
file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS ${HDR_DIR}/*.h)
include_directories(${HDR_DIR})
# sources are always in src/
set(SRCS_DIR	src)
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS ${SRCS_DIR}/*.cpp)

# create library
add_library(${TARGET} STATIC ${HDRS} ${SRCS})
target_include_directories(${TARGET} PUBLIC ${HDR_DIR})

if(OperationArchitecture_build_tests)
    # Include google tests
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest/CMakeLists.txt)
        add_subdirectory (libs/googletest)
    endif()
    #include mock
    add_subdirectory (mock)
    # include tests
    add_subdirectory (test)
endif()

# install library
install(TARGETS ${TARGET} LIBRARY DESTINATION lib)
install(DIRECTORY "${HDR_DIR}" DESTINATION include)
