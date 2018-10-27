#include <iostream>
#include <gtest/gtest.h>
#include <folly/Optional.h>

using namespace std;
using namespace folly;

namespace {
    template<typename V>
    ostream &operator<<(ostream &os, Optional<V> &op) {
        if (op) {
            os << "Optional(" << op.value() << ')';
        }
    }

    struct NoDefault {
        NoDefault(int, int) {}
        char a, b, c;
    };
}

Optional<NoDefault> returnOpt() {
    return Optional<NoDefault>();
}

TEST(Optional, NoDefault) {
    Optional<NoDefault> x;
    EXPECT_FALSE(x);
    x.emplace(4, 5);
    EXPECT_TRUE(bool(x));
    x.clear();
    EXPECT_FALSE(x);
    EXPECT_FALSE(returnOpt());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
