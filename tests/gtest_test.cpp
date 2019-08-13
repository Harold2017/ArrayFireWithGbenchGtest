//
// Created by harold on 13/8/2019.
//

#include <gtest/gtest.h>
#include "gtest_cout.h"
#include <arrayfire.h>

using namespace af;

double ComputeDetminAF(array& A) {
    return det<double>(A);
}

class TestEnvironment : public ::testing::Environment {
public:

    static array getA() {
        static array A(3, 3);
        A = moddims(seq(0, 8), 3, 3);
        return A;
    }

    void SetUp() override {
        getA();
    };

    void TearDown() override {
        GOUT("Completed!");
    }
};

TEST(Test, ComputeDetermin) {
    auto A = TestEnvironment::getA();
    GOUT(ComputeDetminAF(A));
    EXPECT_DOUBLE_EQ(ComputeDetminAF(A), 0.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}
