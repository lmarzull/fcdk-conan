cmake_minimum_required(VERSION 2.8.12)
project(FcdkTest CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(
  test-fcdk
  main.cc
)
target_include_directories(
  test-fcdk
  PRIVATE ${CONAN_INCLUDE_DIRS_FCDK}
)
target_link_libraries(test-fcdk ${CONAN_LIBS_FCDK})

enable_testing()
add_test(NAME test-fcdk
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
         COMMAND test-fcdk)
