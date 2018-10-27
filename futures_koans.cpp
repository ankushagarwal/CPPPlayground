#include <iostream>
#include <gtest/gtest.h>
#include <folly/futures/Future.h>

using namespace std;
using namespace folly;

using std::string;
class MemcacheClient {
public:
    struct GetReply {
        enum class Result {
            FOUND,
            NOT_FOUND,
            SERVER_ERROR,
        };

        Result result;
        // The value when result is FOUND,
        // The error message when result is SERVER_ERROR or CLIENT_ERROR
        // undefined otherwise
        string value;
    };

    GetReply get(string key) {
        return GetReply{.result = GetReply::Result::FOUND, .value = "some value"};
    }

    SemiFuture<GetReply> future_get(string key);
};

TEST(Futures, Basics) {

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
