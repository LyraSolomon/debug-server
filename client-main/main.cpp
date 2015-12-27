#include "client.h"
#include <thread>
int main() {
    //this would be part of robotInit
    char* url="localhost";
    std::thread t1 = std::thread(clientInit, 1678, url);
    t1.join();
    return 0;
}
