#include "snakeengine.h"

// Include standard libraries
#include <sstream>
#include <cstdlib>
#include <cassert>
using namespace std;

#ifdef WITH_OPENCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
#endif

const int SnakeEngine::SCORE_BITE = 10;
const int SnakeEngine::SCORE_DIRECTIONCHANGE = -2;
const int SnakeEngine::SCORE_WALL = -100;
const int SnakeEngine::SCORE_SELFHIT = -100;

SnakeEngine::SnakeEngine(const unsigned & width, const unsigned & height, const unsigned & initialAgentLength) :
    width(width),
    height(height),
    score(0),
    initialAgentLength(initialAgentLength),
    timeStep(0),
    gamePaused(true)
{
    // Snake may not be longer than screen height
    assert(this->initialAgentLength < this->height);

    this->reset();
}

int SnakeEngine::step(const Direction &action)
{
    // On start of game
    this->gamePaused = false;
    if(action == NONE) {
        return this->score;
    }

    // Reference to head of snake
    BlockState& head = this->agent.at(0);

    // Score update
    if(action == head.currentDirection || action == -head.currentDirection) {
        // No score update; in principle no action is taken
    } else {
        // Only penalty on direction change
        this->score += SnakeEngine::SCORE_DIRECTIONCHANGE;
    }

    // Update snake
    Direction nextAction = NONE;
    for(auto &a : this->agent) {
        if(nextAction == NONE) {
            // Head of snake
            nextAction = a.currentDirection;
            // You cannot switch direction by 180 degrees
            if(action != -a.currentDirection) {
                a.currentDirection = action;
            }
        } else {
            // Body of snake
            Direction temp{nextAction};
            nextAction = a.currentDirection;
            a.currentDirection = temp;
        }

        // Update location
        switch(a.currentDirection) {
        case UP:
            a.y--;
            break;
        case DOWN:
            a.y++;
            break;
        case LEFT:
            a.x--;
            break;
        case RIGHT:
            a.x++;
            break;
        default:
            // Do nothing
            break;
        }

        // Check whether snake hits itself
        if(!a.isHead && a.x==head.x && a.y==head.y) {
            // Hit itself!
            this->score += SnakeEngine::SCORE_SELFHIT;
            int oldScore = this->score;
            this->reset();
            return oldScore;
        }
    }

    // Deal with delayed tail additions
    unsigned popCount{0};
    for(auto &i : this->agentAddTailDelay) {
        if(i) {
            i--;
        } else {
            popCount++;
        }
    }
    while(popCount-- > 0) {
        // Pop from vector
        this->agentAddTailDelay.erase(this->agentAddTailDelay.begin());

        // Add to tail
        unsigned xi{this->agent.back().x};
        unsigned yi{this->agent.back().y};
        switch(this->agent.back().currentDirection) {
        case UP:
            yi++;
            break;
        case DOWN:
            yi--;
            break;
        case LEFT:
            xi++;
            break;
        case RIGHT:
            xi--;
            break;
        default:
            // Do nothing
            break;
        }
        this->agent.push_back(BlockState{xi, yi, this->agent.back().currentDirection,false});
    }



    // Check whether bite is eaten
    for(vector<BlockState>::iterator bi = this->bites.begin(); bi != this->bites.end(); bi++) {
        if(head.x == (*bi).x && head.y == (*bi).y) {
            this->bites.erase(bi);
            this->score += SnakeEngine::SCORE_BITE;
            this->addBite();

            // Add bite to tail of snake (with delay)
            this->agentAddTailDelay.push_back(static_cast<unsigned>(this->agent.size())-1);
        }
    }

    // Evaluate position validity (only needed for head)
    if(/* head.x < 0 ||*/ head.x >= this->width || /*head.y < 0 ||*/ head.y >= this->height) {
        // Hit a wall!
        this->score += SnakeEngine::SCORE_WALL;
        int oldScore = this->score;
        this->reset();
        return oldScore;
    }


    // Increase timestep and return current score
    this->timeStep++;
    return this->score;
}

void SnakeEngine::reset()
{
    // Clear board
    this->agent.clear();
    this->bites.clear();
    this->score = 0;
    this->timeStep = 0;
    this->gamePaused = true;

    // Define middle of agent in middle of screen
    this->agent.push_back(BlockState{width/2, height/2-((this->initialAgentLength-1)/2), UP, true});
    for(unsigned i=1; i<this->initialAgentLength; i++) {
        this->agent.push_back(BlockState{this->agent.back().x, this->agent.back().y+1, UP, false});
    }

    // Add single bite
    this->addBite();
}

void SnakeEngine::addBite()
{
    // TODO: takes very long if many bites already exist!

    bool validBite{true};
    BlockState newBite{0, 0, NONE, false};

    do {
        // Generate random position
        validBite = true;
        newBite.x = rand()%this->width;
        newBite.y = rand()%this->height;

        // Check whether bite was already there
        for(auto &b : this->bites) {
            if(b.x == newBite.x && b.y == newBite.y) {
                validBite = false;
                break;
            }
        }

        // Don't check agent if bite is already unvalid
        if(!validBite) break;

        // Check whether (part of) agent is there
        for(auto &a : this->agent) {
            if(a.x == newBite.x && a.y == newBite.y) {
                validBite = false;
                break;
            }
        }

    } while(!validBite);

    // Bite is valid
    this->bites.push_back(newBite);

}

#ifdef WITH_OPENCV
cv::Mat SnakeEngine::getBoard(const unsigned & pixelsPerPosition) const
{
    // Initialize board; Note: colors in [0.0...1.0]; Status area of 50 pixels high
    Mat board = Mat(pixelsPerPosition*this->height + 50, pixelsPerPosition*this->width, CV_64FC4);
    board = Scalar(0.8, 0.8, 0.8);

    // Set status area
    Rect selection(0, pixelsPerPosition*this->height, board.cols, 50);
    board(selection) = Scalar(0.3, 0.3, 0.3);
    stringstream ss;
    ss << "Score: " << this->score;
    putText(board, ss.str(), Point(10, board.rows-15), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 1, 0), 1, 3, false);

    // Draw agent
    for(auto &a : this->agent) {
        // Crop one pixel to keep white borders
        Rect selection(pixelsPerPosition*a.x+1, pixelsPerPosition*a.y+1, pixelsPerPosition-2, pixelsPerPosition-2);
        // Make agent black
        board(selection) = Scalar(0,0,0);
    }

    // Draw bites
    for(auto &b : this->bites) {
        circle(board, Point(pixelsPerPosition*(b.x + 0.5), pixelsPerPosition*(b.y + 0.5)), pixelsPerPosition/2, Scalar(0, 0, 255), -1);
    }

    return board;
}
#endif

unsigned SnakeEngine::getTimeStep() const
{
    return this->timeStep;
}

bool SnakeEngine::isPaused() const
{
    return this->gamePaused;
}

std::vector<BlockState> SnakeEngine::getAgent() const
{
    return this->agent;
}

std::vector<BlockState> SnakeEngine::getBites() const
{
    return this->bites;
}

std::vector<std::vector<unsigned> > SnakeEngine::getStateTable()
{
    vector<vector<unsigned> > stateTable(this->width, vector<unsigned>(this->height, 0));

    // Add agent
    for(BlockState &b : this->agent) {
        if(b.x >= this->width || b.y >= this->height)
            continue;
        stateTable.at(b.x).at(b.y) = 1;
    }

    // Add bites
    for(BlockState &b : this->bites) {
        stateTable.at(b.x).at(b.y) = 2;
    }

    return stateTable;
}

std::vector<double> SnakeEngine::getStateVector()
{
    vector<double> stateVector;

    for(auto &column : this->getStateTable()) {
        for(auto &s : column) {
            stateVector.push_back(static_cast<double>(s));
        }
    }

    return stateVector;
}

double SnakeEngine::getNumberOfStates() const
{
    // Number of possibilities: 3 options per field; hence: 3^numFields
    return pow(3,this->width * this->height);
}
