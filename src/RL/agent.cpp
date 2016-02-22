#include "agent.h"

Agent::Agent(const std::vector<double> & initialState, Environment * e) :
    state(initialState),
    environment(e)
{

}

double Agent::performAction(Action * a)
{
    double R = a->perform();
}

