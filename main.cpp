#include <iostream>
#include <folly/futures/Future.h>

using namespace folly;
using namespace std;

int main() {
    Future<Unit> fu = makeFuture(42).unit();
    cout << fu.isReady();
    return 0;
}