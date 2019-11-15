cmake_minimum_required(VERSION 2.8.12)
project(FcdkTest CXX)

FIND_PACKAGE(gtest REQUIRED)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(
  test-fcdk
  test-CommandLineParser.cc
  test-demangleType.cc
)
target_include_directories(
  test-fcdk
  PRIVATE ${fcdk_INCLUDE_DIRS}
          ${gtest_INCLUDE_DIRS}
)
target_link_libraries(test-fcdk ${gtest_LIBS} ${fcdk_LIBS})

enable_testing()
add_test(NAME test-fcdk
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
         COMMAND test-fcdk)
