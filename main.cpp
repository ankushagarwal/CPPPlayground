#include <glog/logging.h>
#include <folly/Optional.h>
using namespace std;
using namespace folly;


int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = 1;
    FLAGS_minloglevel = 0;
    LOG(INFO) << "Main thread";


    LOG(INFO) << "Exiting main thread";
}
