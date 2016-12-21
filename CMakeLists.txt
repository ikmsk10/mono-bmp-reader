cmake_minimum_required(VERSION 2.8.4)
project(mbmpreader)

# put your needed flags here
set(COMMON_FLAGS "")
set(CMAKE_CXX_FLAGS "-std=c++1z ${COMMON_FLAGS}")
set(CMAKE_C_FLAGS "${COMMON_FLAGS}")

# we just grab all the cpp and h files. not ideal, but works well enough
# means a "reload CMake project" when you add new files
file(GLOB_RECURSE SOURCE_FILES src/*.c src/*.h)
include_directories(src)

# fake target here is never actually built; but has to be here in order for
# CLion to "see" the files and index them.
add_executable(mbmp_reader ${SOURCE_FILES})