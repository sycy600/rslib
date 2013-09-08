project(rslib)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-Wall -std=c++0x")

include_directories(.)

add_subdirectory(vendor/gtest-1.7.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(testrunner testrunner)
aux_source_directory(tests test_src)
add_executable(${testrunner} ${test_src})
target_link_libraries(${testrunner} gtest gtest_main)

add_custom_target(test COMMAND ${testrunner} DEPENDS ${testrunner})
add_custom_target(lint COMMAND python ${PROJECT_SOURCE_DIR}/utils/cpplint.py ${PROJECT_SOURCE_DIR}/rslib/* ${PROJECT_SOURCE_DIR}/tests/*)

