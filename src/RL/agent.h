#ifndef AGENT_H
#define AGENT_H

// Include standard libraries
#include <vector>
#include <utility>
#include <cstdlib>
#include <map>

// Include project libraries
#include "action.h"

class Agent
{
public:
    Agent(const std::vector<double> &initialState, std::vector<Action*> actions, float epsilon=0.9);

    // Agent specific method; choose and perform action
    void performAction();

    // Getters
    std::vector<double> getState() const;
    std::vector<Action*> getActions();
    std::map<std::vector<double>,std::vector<double> > getQTable() const;

private:
    // Add state to knownStates and QTable; returns false if already in there.
    bool addState(const std::vector<double> &s);

private:
    // List of possible actions
    std::vector<Action*> actions;

    // Vector of double's represents state
    std::vector<double> state;

    // Last reward
    double lastReward;

    // State-Action values for Q-Learning
    std::map<std::vector<double>,std::vector<double> > QTable;

    // Exploration factor
    float epsilon;
};

#endif // AGENT_H
