#

## Simple Project Template with GoogleBench and GoogleTest

```bash
.
├── CMakeLists.txt
├── cmake_modules
│   └── FindGoogleBenchmark.cmake
├── docker
│   ├── cuda10_1_ubuntu18_04
│   │   ├── CMakeLists.txt
│   │   ├── Dockerfile
│   │   ├── fft.cpp
│   │   ├── result.md
│   │   └── test_backend.cpp
│   ├── cuda8.0_ubuntu16.04
│   │   └── Dockerfile
│   └── cuda9.2_ubuntu18.04
│       └── Dockerfile
├── install_google_benchmark_and_test.sh
├── main.cpp
├── README.md
├── src
│   └── gbench_test.cpp
└── tests
    ├── gtest_cout.h
    └── gtest_test.cpp
```

Please use `install_google_benchmark_and_test.sh` for `GBench` and `GTest` installation.

Additions:

- `docker` folder includes different versions of `ArrayFire DockerFile`
- useful header `gtest_cout.h` for printing in `GTest`
- useful macro for calculating device memory usage in `gbench_test.cpp`'s `profiler`
