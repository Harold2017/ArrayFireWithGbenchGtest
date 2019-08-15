#

## Simple Project Template with GoogleBench and GoogleTest

```bash
.
├── benchmarks
├── cmake_modules
├── docker
│   ├── cuda10.1_ubuntu18_04
│   ├── cuda8.0_ubuntu16.04
│   └── cuda9.2_ubuntu18.04
├── src
│   ├── sample_files
│   └── utils
└── tests
```

Please use `install_google_benchmark_and_test.sh` for `GBench` and `GTest` installation.

Additions:

- `docker` folder includes different versions of `ArrayFire DockerFile`
- useful header `gtest_cout.h` for printing in `GTest`
- useful macro for calculating device memory usage in `gbench_test.cpp`'s `profiler`
- some samples in `src`
