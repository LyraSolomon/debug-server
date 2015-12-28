#include "vision.h"
#include "server.h"
#include <thread>
#include <iostream>
int main() {
    std::cout<<"press ^C to exit"<<std::endl;
    std::thread t1 = std::thread(serverInit, 1678);
    std::thread t2 = std::thread(CitrusVision::visionInit);
    t1.join();
    t2.join();
    return 0;
}
