#include "config.h"

// Include standard libraries
#include <iostream>
#include <vector>

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
#include "agent.h"
#include "snakeactions.h"

// Namespaces
using namespace std;

int main(int argc, char **argv) {
#ifdef WITH_OPENCV
    // Start the game
    unsigned boardWidth{10}, boardHeight{10};
    SnakeEngine game(boardWidth, boardHeight, 3);

    // Define RL Actions
    vector<Action*> actions;
    actions.push_back(new ActionUp(&game));
    actions.push_back(new ActionDown(&game));
    actions.push_back(new ActionLeft(&game));
    actions.push_back(new ActionRight(&game));

    // Define RL Agent
    Agent agent(game.getStateVector(), actions);

    // Fast training loop
    unsigned maxLoops = 0;
    while(maxLoops--) {
        // RL performs action
        agent.performAction();
    }

    cout << "States explored: " << agent.getQTable().size() << " of " << game.getNumberOfStates() << endl;

    // Visualized loop
    cv::namedWindow("Snake");
    bool keepPlaying{true};
    unsigned timeStep = 10; // in [ms]; 0 means as fast as SnakeEngine::step() is called (e.g., for AI)

    while(keepPlaying) {
        // RL performs action
        agent.performAction();

        // Print explored states
        cout << "States explored: " << agent.getQTable().size() << " of " << game.getNumberOfStates() << endl;

        // Display board
        imshow("Snake", game.getBoard());

        // Process keyboard input
        int keyPress = waitKey(timeStep) & 0xFF;
        switch(keyPress) {
            // To quit: press ESC
            case 27:
                keepPlaying = false;
                break;
        }
    }

    // End of program - delete pointers
    for(Action* a : actions) {
        delete a;
    }
#endif

    return 0;
}
