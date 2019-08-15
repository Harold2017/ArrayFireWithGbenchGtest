//
// Created by harold on 15/8/2019.
//

#ifndef ARRYFIRE_GBENCH_GTEST_UTILS_H
#define ARRYFIRE_GBENCH_GTEST_UTILS_H

#include <arrayfire.h>
#include <string>
#include <chrono>
#include <iostream>

namespace Utils {
    namespace Profiler {
        struct profiler
        {
            std::string name;
            std::chrono::high_resolution_clock::time_point p;
            explicit profiler(std::string n) :
                    name(std::move(n)), p(std::chrono::high_resolution_clock::now()) { }
            ~profiler()
            {
                using dura_nano = std::chrono::nanoseconds;
                using dura_micro = std::chrono::microseconds;
                using dura_mili = std::chrono::milliseconds;
                using dura_sec = std::chrono::seconds;
                auto d = std::chrono::high_resolution_clock::now() - p;
                std::cout << name << ": "
                          << std::chrono::duration_cast<dura_nano>(d).count()
                          << " ns, "
                          << std::chrono::duration_cast<dura_micro >(d).count()
                          << " us, "
                          << std::chrono::duration_cast<dura_mili >(d).count()
                          << " ms, "
                          << std::chrono::duration_cast<dura_sec >(d).count()
                          << " s"
                          << std::endl;
            }
        };
    }
    class utils {
    public:
        static void read_file_into_array(const std::string& path_name, af::array &data);
    };
}

#define PROFILE_BLOCK(pbn) Utils::Profiler::profiler _pfinstance(pbn)

#endif //ARRYFIRE_GBENCH_GTEST_UTILS_H
