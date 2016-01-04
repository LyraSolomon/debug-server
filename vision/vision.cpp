#include "vision.h"
#include <iostream>
#include <vector>
namespace CitrusVision {
float x=0, y=0;
bool found=false;
void visionInit() {
#ifndef DISABLE_VISION
    using namespace cv;
    using namespace std;
    cv::VideoCapture cap;
    cv::Mat m=cv::Mat(100, 100, CV_32F, cv::Scalar(255, 255, 255));
    cv::namedWindow("webcam", CV_WINDOW_AUTOSIZE);
    cv::imshow("webcam", m);
    waitKey(20);
    std::cout<<"opening webcam (this will take about 10 seconds)\n";
    if(!cap.open(0)) {
        std::cout<< "could not open camera";
        exit(0);
    }
    cv::namedWindow("webcam");
    while(true) {
        cap >> m;
        blur(m, m, Size(5, 5));
        //inRange(m, Scalar(0, 0, 50), Scalar(120, 60, 256), m);
        inRange(m, Scalar(0, 0, 50), Scalar(50, 50, 256), m);
        int erosion_size=15;
        erode(m, m, getStructuringElement(MORPH_RECT,
                    Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                    Point( erosion_size, erosion_size )));

        dilate(m, m, getStructuringElement(MORPH_RECT,
                    Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                    Point( erosion_size, erosion_size )));
        //threshhold
        //inRange(m, Scalar(0, 0, 0), Scalar(0, 0, 0), m);
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours( m.clone(), contours, hierarchy,
                    CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
        for( unsigned int i = 0; i < contours.size(); i++ )
        {
            approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        }
        int maxArea=0;//index of rect with biggest area
        if (contours.size()==0) {found=false;}
        else {
            for( unsigned int i = 0; i< contours.size(); i++ ) {
                if (boundRect[i].area()>400){
                    if (boundRect[i].area()>boundRect[maxArea].area()) maxArea=i;
                    rectangle( m, boundRect[i].tl(), boundRect[i].br(), Scalar(255), 2, 8, 0 );
                }
            }
            x=(boundRect[maxArea].tl().x+boundRect[maxArea].br().x)/2;
            y=(boundRect[maxArea].tl().y+boundRect[maxArea].br().y)/2;
            x=x/m.cols-0.5;
            y=y/m.rows-0.5;
            cout<<"x="<<x<<" y="<<y<<endl;
        }
        cv::imshow("webcam", m);
        waitKey(20);
    }
#else
#warning DISABLE_VISION has been defined. to enable vision, comment out the line in vision/BUILD.
#endif
}
}// namespace CitrusVision
