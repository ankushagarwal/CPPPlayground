#include <folly/futures/Future.h>
#include <folly/executors/ThreadedExecutor.h>
#include <glog/logging.h>

using namespace std;
using namespace folly;

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = 1;
    FLAGS_minloglevel=0;

    folly::ThreadedExecutor executor;
    auto pair = makePromiseContract<int>();
    Promise<int> promise = std::move(pair.first);
    executor.add([&promise]() {
        LOG(INFO) << "Inside executor";
//        this_thread::sleep_for(std::chrono::milliseconds(100));
        promise.setValue(100);
        LOG(INFO) << "Completed executor";
    });

    Future<Unit> fu = std::move(pair.second)
            .via(&executor)
            .within(std::chrono::milliseconds(20))
            .onError([](FutureTimeout &e) {
                LOG(INFO) << "FutureTimeout: " << e.what();
                return -1;
            }).thenValue([](int i){
                LOG(INFO) << "Got " << i;
            });
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    LOG(ERROR) << "Exiting main thread";
}
