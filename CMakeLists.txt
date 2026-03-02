cmake_minimum_required(VERSION 3.26)

project(KEUL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE TEST_SRC "${CMAKE_SOURCE_DIR}/tests/*.cpp")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(/utf-8)
endif ()


message(STATUS "building: library unit tests")
add_executable(test-keul ${TEST_SRC})
target_include_directories(test-keul PRIVATE "${CMAKE_SOURCE_DIR}/include")
# target_link_libraries(KEUL PRIVATE stdc++exp) # uncomment if experimental needed (gcc)

# examples/ 

list(APPEND examples string-utilities benchmark timer unit-tests)

foreach(example IN LISTS examples)
	message(STATUS "building: ${example}")
	add_executable(${example} examples/${example}.cpp)
	target_include_directories(${example} PRIVATE "${CMAKE_SOURCE_DIR}/include")
endforeach()