#

## Simple Project Template with GoogleBench and GoogleTest

```bash
.
├── CMakeLists.txt
├── cmake_modules
│   └── FindGoogleBenchmark.cmake
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

- useful header `gtest_cout.h` for printing in `GTest`
- useful macro for calculating device memory usage in `gbench_test.cpp`'s `profiler`
