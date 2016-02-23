#include "agent.h"

Agent::Agent(const std::vector<double> & initialState, std::vector<Action *> actions) :
    actions(actions),
    state(initialState)
{
    // Add initial state to knownStates

}

void Agent::performAction()
{
    // Select non-greedy action
    unsigned actionIndex = rand() % this->actions.size();
    Action *a = this->actions.at(actionIndex);

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

std::vector<std::vector<double> > Agent::getKnownStates() const
{
    return this->knownStates;
}

std::vector<Action *> Agent::getActions()
{
    return this->actions;
}

bool Agent::addState(const std::vector<double> & s)
{
    // Check whether state is already in knownStates
    for(auto &ks : this->knownStates) {
        if(s == ks) {
            return false;
        }
    }

    // Add state to state vector
    this->knownStates.push_back(s);

    // Add state to QTable
    for(unsigned i=0; i<this->actions.size(); i++) {
        // Only add indices
        this->QTable.push_back(std::pair<unsigned,unsigned>(this->knownStates.size()-1, i));
    }

    return true;
}

