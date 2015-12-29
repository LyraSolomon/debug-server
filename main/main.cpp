#include "server.h"
#include <thread>
#include <iostream>
int main() {
    std::cout<<"press ^C to exit"<<std::endl;
    std::thread t1 = std::thread(serverInit, 80);
    t1.join();
    return 0;
}
