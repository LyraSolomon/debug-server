#include "reader.h"
#include <thread>
#include <mutex>

cv::Mat frame;
std::mutex mutex;

cv::Mat getFrame() {
        std::lock_guard<std::mutex> guard(mutex);
        return frame.clone();
}

void runReader() {
        while
