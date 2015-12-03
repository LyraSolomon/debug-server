#include "vision.h"
#include "server.h"
#include <thread>
int main() {
    std::thread t1 = std::thread(serverInit, 1678);
    std::thread t2 = std::thread(CitrusVision::visionInit);
    while(true) std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
