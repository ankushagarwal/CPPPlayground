#include <folly/futures/Future.h>
#include <folly/executors/ThreadedExecutor.h>
#include <glog/logging.h>

using namespace std;
using namespace folly;

class ManualExecutor : public Executor {
private:
    int i_;

public:
    explicit ManualExecutor(int i) : i_(i) {}
    void add(Func f) override {
        LOG(INFO) << i_ << " Pushed work onto executor";
        LOG(INFO) << i_ << " Starting a new thread for executing the work";
        thread th(move(f));
        th.detach();
    }
};

void foo(string msg, int ms = 100) {
    LOG(INFO) << msg << " started";
    this_thread::sleep_for(chrono::milliseconds(ms));
    LOG(INFO) << msg << " completed";
}

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = 1;
    FLAGS_minloglevel = 0;
    LOG(INFO) << "Main thread";

    shared_ptr<ManualExecutor> e1 = make_shared<ManualExecutor>(1);
    shared_ptr<ManualExecutor> e2 = make_shared<ManualExecutor>(2);
    auto x = e1.get();
    via(e1.get(), []() {
        foo("first item", 1000);
    }).then([](){
        foo("second item", 1000);
    }).via(e2.get()).then([](){
        foo("third item", 1000);
    });
    LOG(INFO) << "Sleeping main thread";
    this_thread::sleep_for(chrono::milliseconds(10000));
    LOG(INFO) << "Exiting main thread";
}
