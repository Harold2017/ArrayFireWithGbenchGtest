//
// Created by harold on 7/19/19.
//

#ifndef GTEST_COUT_H
#define GTEST_COUT_H

#include "gtest/gtest.h"

namespace testing
{
    namespace internal
    {
        enum GTestColor
        {
            COLOR_DEFAULT, COLOR_RED, COLOR_GREEN, COLOR_YELLOW
        };
        extern void ColoredPrintf(GTestColor color, const char* fmt, ...);
    }
}

#define GOUT(STREAM) \
    do \
    { \
        std::stringstream ss; \
        ss << STREAM << std::endl; \
        testing::internal::ColoredPrintf(testing::internal::COLOR_GREEN, "[          ] "); \
        testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, ss.str().c_str()); \
    } while (false); \

#endif //GTEST_COUT_H
