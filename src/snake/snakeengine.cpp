#include "snakeengine.h"

// Include standard libraries
#include <sstream>
using namespace std;

#ifdef WITH_OPENCV
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
#endif

SnakeEngine::SnakeEngine(const unsigned & width, const unsigned & height, const unsigned & initialAgentLength) :
    width(width),
    height(height),
    score(0)
{
    // Define middle of agent in middle of screen
    this->agent.push_back(Position{width/2, height/2-((initialAgentLength-1)/2)});
    for(unsigned i=1; i<initialAgentLength; i++) {
        this->agent.push_back(Position{this->agent.back().x, this->agent.back().y+1});
    }

}

#ifdef WITH_OPENCV
cv::Mat SnakeEngine::getBoard(const unsigned & pixelsPerPosition) const
{
    Mat board = Mat::ones(pixelsPerPosition*this->height, pixelsPerPosition*this->width, CV_32F);

    // Draw agent
    for(auto &a : this->agent) {
        // Crop one pixel to keep white borders
        Rect selection(pixelsPerPosition*a.x+1, pixelsPerPosition*a.y+1, pixelsPerPosition-2, pixelsPerPosition-2);
        // Make agent black
        board(selection) = 0;
    }

    // Write score
    stringstream ss;
    ss << "Score: " << this->score;
    circle();
    putText(board, ss.get(), Point(10, 10), FONT_HERSHEY_SIMPLEX, 5, Scalar(0, 255, 0), 1, 8, true);

    return board;
}
#endif
