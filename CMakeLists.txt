project(rslib)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")

include_directories(.)

aux_source_directory(rslib src)
add_library(rslib STATIC ${src})

set(testrunner testrunner)
add_subdirectory(vendor/gtest-1.7.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
aux_source_directory(tests test_src)
add_executable(${testrunner} ${test_src})
target_link_libraries(${testrunner} gtest gtest_main rslib)

install(TARGETS rslib ARCHIVE DESTINATION lib)
install(DIRECTORY rslib DESTINATION include FILES_MATCHING PATTERN "*.h")

add_custom_target(test COMMAND ${testrunner} DEPENDS ${testrunner})
add_custom_target(lint COMMAND python ${PROJECT_SOURCE_DIR}/utils/cpplint.py --filter=-readability/streams ${PROJECT_SOURCE_DIR}/rslib/* ${PROJECT_SOURCE_DIR}/tests/*)
add_custom_target(memcheck COMMAND valgrind --tool=memcheck --leak-check=yes --error-exitcode=1 ./${testrunner})
add_custom_target(doc COMMAND bash ${PROJECT_SOURCE_DIR}/utils/run_doxygen.sh ${PROJECT_SOURCE_DIR}/rslib ${PROJECT_SOURCE_DIR}/utils/Doxyfile)

