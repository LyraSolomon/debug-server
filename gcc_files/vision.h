#ifndef _VISION_H_
#define _VISION_H_

#ifndef DISABLE_VISION
#include "opencv2/opencv.hpp"
#endif
namespace CitrusVision {
    extern float x, y;
    void visionInit();
}

#endif
