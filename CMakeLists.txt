cmake_minimum_required(VERSION 3.14)
project(laplace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenMP REQUIRED)


# Add source files for laplace-omp executable
add_executable(
  laplace-omp.x
  ${CMAKE_SOURCE_DIR}/laplace-omp.cpp
  ${CMAKE_SOURCE_DIR}/main-omp.cpp)
target_include_directories(laplace-omp.x PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(laplace-omp.x PRIVATE OpenMP::OpenMP_CXX)
