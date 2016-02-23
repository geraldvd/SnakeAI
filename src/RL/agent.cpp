#include "agent.h"

Agent::Agent(const std::vector<double> & initialState, std::vector<Action *> actions) :
    actions(actions),
    state(initialState)
{

}

void Agent::nonGreedyAction()
{
    // Pick random action
    unsigned actionIndex = rand() % this->actions.size();

    // Perform action
    this->performAction(this->actions.at(actionIndex));
}

void Agent::performAction(Action * a)
{
    std::pair<double,std::vector<double> > actionReturn = a->perform();

    // Set new state
    this->state = actionReturn.second;

    // Set new reward
    this->lastReward = actionReturn.first;
}

