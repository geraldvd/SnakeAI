#include "config.h"

// Include standard libraries

#ifdef WITH_QT
    #include <QApplication>
#endif

#ifdef WITH_OPENCV
    #include <opencv2/core.hpp>
    #include <opencv2/highgui.hpp>
    using namespace cv;
#endif

// Include project files
#include "snakeengine.h"

// Namespaces
using namespace std;

int main(int argc, char **argv) {
    // Initialize
    namedWindow("Snake");
    bool keepPlaying{true};
    SnakeEngine game;

    // Main game loop
    while(keepPlaying) {

        // Display board
        imshow("Snake", game.getBoard());


        // Process keyboard input
        int keyPress = waitKey(1) & 0xFF;
        switch(keyPress) {
        case 'q': case 'Q':
            // User pressed q/Q
            keepPlaying = false;
            break;
        }
    }


    return 0;
}
