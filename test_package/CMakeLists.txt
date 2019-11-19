cmake_minimum_required(VERSION 2.8.12)
project(FcdkTest CXX)

FIND_PACKAGE(fcdk REQUIRED)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(
  test-fcdk
  main.cc
)
target_compile_features(test-fcdk PUBLIC cxx_std_17)
target_include_directories(
  test-fcdk
  PRIVATE ${CONAN_INCLUDE_DIRS}
)
MESSAGE("---> ${fcdk_LIBS}")
target_link_libraries(test-fcdk ${fcdk_LIBRARIES})

enable_testing()
add_test(NAME test-fcdk
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
         COMMAND test-fcdk)
