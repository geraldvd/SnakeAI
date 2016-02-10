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

// Namespaces
using namespace std;

int main(int argc, char **argv) {
    // Initialize game
    SnakeEngine game(35,35,7);

#ifdef WITH_OPENCV
    // Initialize
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
        cout << "kjsljdf    " << rand()%50 << endl;
        switch(keyPress) {
        // To quit: press ESC
        case 27:
            keepPlaying = false;
            break;
        // To reset: press RETURN
        case 10:
            game.reset();
            nextAction = NONE;
            break;
        // Arrow keys
        case 82:
            nextAction = UP;
            break;
        case 84:
            nextAction = DOWN;
            break;
        case 81:
            nextAction = LEFT;
            break;
        case 83:
            nextAction = RIGHT;
            break;
        }
    }
#endif


    return 0;
}
