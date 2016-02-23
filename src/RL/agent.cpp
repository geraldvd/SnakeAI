#include "agent.h"

Agent::Agent(const std::vector<double> & initialState, std::vector<Action *> actions, float epsilon) :
    actions(actions),
    state(initialState),
    epsilon(epsilon)
{
}

void Agent::performAction()
{
    float r{static_cast<float>(rand()) / RAND_MAX};
    Action *a{NULL};
    if(this->epsilon < r) {
        // Exploration: Select non-greedy action
        unsigned actionIndex = rand() % this->actions.size();
        a = this->actions.at(actionIndex);
    } else {
        // Exploitation
        if(this->QTable.count(this->state)) {
            std::vector<double> possibleActions = this->QTable[this->state];
            double maxQ = possibleActions.at(0);
            unsigned indexMaxQ = 0;
            for(unsigned i=1; i<possibleActions.size(); i++) {
                if(maxQ < possibleActions.at(i)) {
                    maxQ = possibleActions.at(i);
                    indexMaxQ = i;
                }
            }
            a = this->actions.at(indexMaxQ);
        } else {
            // Exploration: Select non-greedy action
            unsigned actionIndex = rand() % this->actions.size();
            a = this->actions.at(actionIndex);
        }
    }


    // Perform action, and set state and reward
    std::pair<double,std::vector<double> > actionReturn = a->perform();
    this->state = actionReturn.second;
    this->addState(actionReturn.second);
    this->lastReward = actionReturn.first;
}

std::vector<double> Agent::getState() const
{
    return this->state;
}

std::vector<Action *> Agent::getActions()
{
    return this->actions;
}

std::map<std::vector<double>, std::vector<double> > Agent::getQTable() const
{
    return this->QTable;
}

bool Agent::addState(const std::vector<double> & s)
{
    // Check whether state is already in QTable
    if(this->QTable.count(s))
        return false;

    // Add state to QTable
    std::pair<std::vector<double>,std::vector<double> > newQValue(s, std::vector<double>(this->actions.size(), 0.0));
    this->QTable.insert(newQValue);

    return true;
}

