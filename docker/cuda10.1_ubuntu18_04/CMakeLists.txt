cmake_minimum_required(VERSION 3.12.2)
project(example_bench)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

find_package(ArrayFire REQUIRED)

add_executable(example_bench
        # fft.cpp
        test_backend.cpp
        )

# target_link_libraries(example_bench ArrayFire::afcpu)
# target_link_libraries(example_bench ArrayFire::afcuda)
target_link_libraries(example_bench ArrayFire::af)
