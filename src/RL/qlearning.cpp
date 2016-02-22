#include "qlearning.h"



QLearning::QLearning(const unsigned & arenaSizeX, const unsigned & arenaSizeY, const State & initialState, const double & initialValue) :
    state(initialState),
    value(initialValue)
{
}
