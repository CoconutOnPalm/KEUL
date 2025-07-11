cmake_minimum_required(VERSION 3.26)

project(KEUL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE TEST_SRC "${CMAKE_SOURCE_DIR}/tests/*.cpp")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(/utf-8)
endif ()


message(STATUS "building: library unit tests")
add_executable(library_unit_tests test.cpp ${TEST_SRC})
target_include_directories(library_unit_tests PRIVATE "${CMAKE_SOURCE_DIR}/include")
# target_link_libraries(KEUL PRIVATE stdc++exp) # uncomment if experimental needed (gcc)

# examples/ 

list(APPEND Examples StringUtilities Benchmark Timer UnitTests)

foreach(example IN LISTS Examples)
	message(STATUS "building: ${example}")
	add_executable(${example} examples/${example}.cpp)
	target_include_directories(${example} PRIVATE "${CMAKE_SOURCE_DIR}/include")
endforeach()