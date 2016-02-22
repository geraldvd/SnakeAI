#include "config.h"

// Include standard libraries
#include <iostream>

#ifdef WITH_QT
    #include <QApplication>
#endif

#ifdef WITH_OPENCV
    #include <opencv2/core/core.hpp>
    #include <opencv2/highgui/highgui.hpp>
    #include <opencv2/core/utility.hpp>
    using namespace cv;
#endif

// Include project files
#include "snakeengine.h"
#ifdef USE_RL
    #include "agent.h"
    #include "environment.h"
#endif

// Namespaces
using namespace std;

int main(int argc, char **argv) {
#ifdef USE_RL
    // Start the game
    SnakeEngine game(35, 35, 3);

    // Define RL environment, agent and actions
    Agent agent();


#else
#ifdef WITH_OPENCV
    // Initialize
    SnakeEngine game(35, 35, 3);
    cv::namedWindow("Snake");
    bool keepPlaying{true};
    unsigned timeStep = 100; // in [ms]; 0 means as fast as SnakeEngine::step() is called (e.g., for AI)
    Direction nextAction{NONE};

    // Main game loop
    while(keepPlaying) {
        // Perform action
        nextAction = game.isPaused() ? NONE : nextAction;
        game.step(nextAction);

        // Display board
        imshow("Snake", game.getBoard());

        // Process keyboard input
        int keyPress = waitKey(timeStep) & 0xFF;
        switch(keyPress) {
        // To quit: press ESC
        case 27:
            keepPlaying = false;
            break;
        // To reset: press RETURN
#ifdef __APPLE__
        case 13:
#else
        case 10:
#endif
            game.reset();
            nextAction = NONE;
            break;
        // Arrow keys
#ifdef __APPLE__
        case 0:
#else
        case 82:
#endif
            nextAction = UP;
            break;
#ifdef __APPLE__
        case 1:
#else
        case 84:
#endif
            nextAction = DOWN;
            break;
#ifdef __APPLE__
        case 2:
#else
        case 81:
#endif
            nextAction = LEFT;
            break;
#ifdef __APPLE__
        case 3:
#else
        case 83:
#endif
            nextAction = RIGHT;
            break;
        }
    }
#endif // WITH_OPENCV
#endif // USE_RL


    return 0;
}
