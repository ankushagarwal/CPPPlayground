#include <iostream>
#include <gtest/gtest.h>
#include <folly/futures/Future.h>

using namespace std;
using namespace folly;

TEST(Values, canonicalForm) {
    Future<int> answer(42);
    EXPECT_EQ(42, std::move(answer).get());
}

TEST(Values, typeDeduction) {
    // If you use makeFuture, the compiler will deduce the type.
    auto answer = makeFuture(42);
    EXPECT_EQ(42, std::move(answer).get());
}

TEST(Values, exceptionNeedsType) {
    // To create a Future holding an exception, you must
    // use makeFuture with the type
    std::runtime_error err("Don't Panic");
    auto question = makeFuture<std::runtime_error>(err);
    // not
    //auto question = makeFuture(err);
    EXPECT_THROW(std::move(question).get(), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
