#ifndef SNAKEENGINE_H
#define SNAKEENGINE_H

#include "config.h"

// Include standard libraries
#include <vector>

#ifdef WITH_OPENCV
    // Include OpenCV libraries
    #include <opencv2/core/core.hpp>
#endif

// Include project files
#include "snakeutils.h"

class SnakeEngine
{
public:
    SnakeEngine(const unsigned &width=25, const unsigned &height=25, const unsigned &initialAgentLength=3);

#ifdef WITH_OPENCV
    cv::Mat getBoard(const unsigned &pixelsPerPosition=20) const;
#endif

private:
    unsigned width;
    unsigned height;
    int score;

    std::vector<Position> agent;
    std::vector<Position> bites;
};

#endif // SNAKEENGINE_H
