#ifndef AGENT_H
#define AGENT_H

// Include standard libraries
#include <vector>

// Include project libraries
#include "action.h"
#include "environment.h"

class Agent
{
public:
    Agent(const std::vector<double> &initialState, Environment *e);

    // Agent specific method; returns reward.
    double performAction(Action *a);

private:
    // Vector of double's represents state
    std::vector<double> state;

    // Pointer to environment
    Environment *environment;

};

#endif // AGENT_H
