//
// Created by harold on 13/8/2019.
//

#include <benchmark/benchmark.h>
#include <chrono>
#include <iostream>
#include <arrayfire.h>

using af::array;

struct profiler
{
    size_t alloc_bytes{}, alloc_buffers{}, lock_bytes{}, lock_buffers{};
    benchmark::Counter* cnt;
    explicit profiler(benchmark::State& state){
        state.counters["bytes"] =
                benchmark::Counter(0,
                                   benchmark::Counter::kIsIterationInvariantRate,
                                   benchmark::Counter::OneK::kIs1024);
        cnt = &state.counters["bytes"];
        af::deviceMemInfo(&alloc_bytes, &alloc_buffers, &lock_bytes, &lock_buffers);
    }
    ~profiler()
    {
        size_t alloc_bytes2, alloc_buffers2, lock_bytes2, lock_buffers2;
        af::deviceMemInfo(&alloc_bytes2, &alloc_buffers2, &lock_bytes2, &lock_buffers2);

        *cnt = (alloc_bytes2 - alloc_bytes);
    }
};

#define PROFILE_BLOCK(st) profiler _pfinstance(st)

double ComputeDetermin(const double *mat) {
    double det_mat = (*mat) * ((*(mat + 3)) * (*(mat + 5)) - (*(mat + 4)) * (*(mat + 4)))
                     - (*(mat + 1)) * ((*(mat + 1)) * (*(mat + 5)) - (*(mat + 2)) * (*(mat + 4)))
                     + (*(mat + 2)) * ((*(mat + 1)) * (*(mat + 4)) - (*(mat + 2)) * (*(mat + 3)));

    return det_mat;
}

double ComputeDetminAF(array& A) {
    return af::det<double>(A);
}

static void BM_DetArrayFire(benchmark::State &state) {
    {
        PROFILE_BLOCK(state);
        af::sync();
        for (auto _ : state) {
            array A = af::randu(3, 3, f32);
            ComputeDetminAF(A);
            af::sync();
        }
    }
    af::deviceGC();
}

BENCHMARK(BM_DetArrayFire)->MeasureProcessCPUTime()->UseRealTime()->Unit(benchmark::kMicrosecond);

static void BM_Homemade(benchmark::State &state) {
    {
        PROFILE_BLOCK(state);
        auto A = af::moddims(af::seq(0, 8), 3, 3);
        af::sync();
        static double mat[] = {};
        std::vector<double> v (af::flat(A).elements());
        std::copy(v.begin(), v.end(), mat);
        for (auto _ : state)
            ComputeDetermin(mat);
        af::sync();
    }
    af::deviceGC();
}

BENCHMARK(BM_Homemade);

int main(int argc, char** argv) {
    char device_name[256];
    char platform[256];
    char toolkit[256];
    char compute[256];
    af::deviceInfo(device_name, platform, toolkit, compute);

    int major, minor, patch;
    af_get_version(&major, &minor, &patch);
    const char* revision = af_get_revision();

    printf("Context:\n"
           "ArrayFire v%d.%d.%d (%s) (Backend: %s Platform: %s)\n"
           "Device: %s (%s %s)\n",
           major, minor, patch, revision, platform, platform,
           device_name, compute, toolkit);

    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
}
