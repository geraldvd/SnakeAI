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

    // Agent specific method; choose and perform action
    void performAction();

    // Getters
    std::vector<double> getState() const;
    std::vector<std::vector<double> > getKnownStates() const;
    std::vector<Action*> getActions();

private:
    // Add state to knownStates and QTable; returns false if already in there.
    bool addState(const std::vector<double> &s);

private:
    // List of possible actions
    std::vector<Action*> actions;

    // Vector of double's represents state
    std::vector<double> state;

    // List of possible (known) states
    std::vector<std::vector<double> > knownStates;

    // Last reward
    double lastReward;

    // State-Action values for Q-Learning
    std::vector<std::pair<unsigned,unsigned> > QTable;
};

#endif // AGENT_H
