#ifndef SNAKEENGINE_H
#define SNAKEENGINE_H

#include "config.h"

// Include standard libraries
#include <vector>

#ifdef WITH_OPENCV
    // Include OpenCV libraries
    #include <opencv2/core/core.hpp>
#endif

enum Direction {
    NONE=0, UP=-1, DOWN=1, LEFT=-2, RIGHT=2
};

struct BlockState {
    unsigned x;
    unsigned y;
    Direction currentDirection;
    bool isHead;
    int stepsToHide;
};

class SnakeEngine
{
public:
    SnakeEngine(const unsigned &width=25, const unsigned &height=25, const unsigned &initialAgentLength=3);
    int step(const Direction &action);
    void reset();
    void addBite();

#ifdef WITH_OPENCV
    cv::Mat getBoard(const unsigned &pixelsPerPosition=20) const;
#endif

    unsigned getTimeStep() const;
    bool isPaused() const;

private:
    unsigned width;
    unsigned height;
    int score;
    unsigned initialAgentLength;
    unsigned timeStep;
    bool gamePaused;

    std::vector<BlockState> agent;
    std::vector<BlockState> bites;

    // constants
    static const int SCORE_BITE;
    static const int SCORE_DIRECTIONCHANGE;
    static const int SCORE_WALL;
    static const int SCORE_SELFHIT;
};

#endif // SNAKEENGINE_H
