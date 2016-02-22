#ifndef AGENT_H
#define AGENT_H

// Include standard libraries
#include <vector>

class Agent
{
public:
    Agent();

    // Agent specific method; returns reward.
    virtual double performAction() = 0;

private:
    // Vector of double's represents state
    std::vector<double> state;

};

#endif // AGENT_H
