#include "vision.h"
#include <iostream>
namespace CitrusVision {
float x=0, y=0;
void visionInit() {
    using namespace cv;
    cv::VideoCapture cap;
    cv::Mat m=cv::Mat(100, 100, CV_32F, cv::Scalar(255, 255, 255));
    cv::namedWindow("webcam", CV_WINDOW_AUTOSIZE);
    cv::imshow("webcam", m);
    waitKey(20);
    std::cout<<"opening webcam (this will take about 10 seconds)\n";
    if(!cap.open(1)) {
        std::cout<< "could not open camera";
        exit(0);
    }
    cv::namedWindow("webcam");
    while(true) {
        cap >> m;
        cv::imshow("webcam", m);
        waitKey(20);
        x=1;
        y=2;
    }
}
}// namespace CitrusVision
