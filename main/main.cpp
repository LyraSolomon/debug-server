#include "vision.h"
#include "server.h"
#include "reader.h"
#include <thread>
#include <iostream>
int main() {
    std::cout<<"press ^C to exit"<<std::endl;
    //ORDER MATTERS! runReader needs to finish initializing before visionInit does.
    std::thread t3 = std::thread(runReader);
    std::thread t1 = std::thread(serverInit, 1678);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread t2 = std::thread(CitrusVision::visionInit);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
