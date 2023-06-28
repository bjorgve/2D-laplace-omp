cmake_minimum_required(VERSION 3.14)
project(laplace LANGUAGES CXX)

find_package(OpenMP REQUIRED)

# Add source files for laplace-omp executable
set(SOURCE_FILES
    laplace-omp.cpp
    main-omp.cpp)

add_executable(laplace-omp.x ${SOURCE_FILES})

# Set the C++ standard and disable extensions for the laplace-omp.x target
target_compile_features(laplace-omp.x PRIVATE cxx_std_17)
set_target_properties(laplace-omp.x PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(laplace-omp.x PRIVATE OpenMP::OpenMP_CXX)
