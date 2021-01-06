cmake_minimum_required(VERSION 3.9)

set(CMAKE_VERBOSE_MAKEFILE on)
SET(CMAKE_CXX_FLAGS_RELEASE -O3)
project (eightqueen LANGUAGES CXX VERSION 1.0.0)

add_compile_options(-std=c++17)

set(HEADER_FILES include/board.h include/queen.h include/safe.h)
set(SRC src/main.cc)

find_package(Threads REQUIRED)

add_executable(eightqueens ${HEADER_FILES} ${SRC} src/main.cc)
target_include_directories(eightqueens PRIVATE include)
target_link_libraries(eightqueens m)

enable_testing()

set(GTEST_INCLUDE /usr/src/googletest/googletest/include)

include(GoogleTest)
add_executable(viewtest test/viewtest.cc)
target_include_directories(viewtest PRIVATE include ${GTEST_INCLUDE})
target_link_libraries(viewtest -L../gtest/lib gtest gmock gtest_main pthread m)
gtest_add_tests(viewtest test test/viewtest.cc)

add_executable(queentest test/queentest.cc)
target_include_directories(queentest PRIVATE include ${GTEST_INCLUDE})
target_link_libraries(queentest -L../gtest/lib gtest gmock gtest_main pthread m)
gtest_add_tests(queentest test test/queentest.cc)

add_executable(boardtest test/boardtest.cc)
target_include_directories(boardtest PRIVATE include ${GTEST_INCLUDE})
target_link_libraries(boardtest -L../gtest/lib gtest gmock gtest_main pthread m)
gtest_add_tests(boardtest test test/boardtest.cc)

