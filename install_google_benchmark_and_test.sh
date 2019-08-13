#!/bin/bash

set -e  # exit when error

CURRENT_DIR="$(pwd)"
echo "Current dir is: $CURRENT_DIR"
TMP_DIR=/tmp
echo "tmp dir is: $TMP_DIR"

base_components(){
    sudo apt-get update && sudo apt-get -y install git cmake build-essential gcc g++
}

install_google_benchmark_and_test(){
    cd $TMP_DIR && rm -rf google_benchmark
    git clone https://github.com/google/benchmark.git google_benchmark
    cd google_benchmark && git clone https://github.com/google/googletest.git
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make -j$(nproc)
    # to install globally
    sudo make install
}

main(){
    base_components
    install_google_benchmark_and_test
}

main
