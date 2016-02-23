#ifndef AGENT_H
#define AGENT_H

// Include standard libraries
#include <vector>
#include <utility>
#include <cstdlib>

// Include project libraries
#include "action.h"

class Agent
{
public:
    Agent(const std::vector<double> &initialState, std::vector<Action*> actions);

    // Policy's
    void nonGreedyAction();

private:
    // Agent specific method; returns reward.
    void performAction(Action *a);

private:
    // List of possible actions
    std::vector<Action*> actions;

    // Vector of double's represents state
    std::vector<double> state;

    // Last reward
    double lastReward;

};

#endif // AGENT_H
