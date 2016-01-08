#include "reader.h"
#include <thread>
#include <iostream>
#include <mutex>
using namespace cv;
cv::Mat frame;
std::mutex mutex;

cv::Mat getFrame() {
        mutex.lock();
        cv::Mat m=frame.clone();
        mutex.unlock();
        return m;
}

void runReader() {
        cv::VideoCapture cap;
        mutex.lock();
        frame=cv::Mat(100, 100, CV_32F, cv::Scalar(255, 255, 255));
        mutex.unlock();
        if(!cap.open(0)) {
                std::cout<<"can't connect"<<std::endl;
                return;
        }
        while(true) {
                if(cap.isOpened()) {
                        mutex.lock();
                        cap.read(frame);
                        mutex.unlock();
                }
                else {
                        std::cout<<"loading"<<std::endl;
                }
        }
}
