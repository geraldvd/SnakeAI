#ifndef QLEARNING_H
#define QLEARNING_H

// Include standard libraries
#include <vector>

// Definitions
struct Field {
    unsigned x{0};
    unsigned y{0};
    unsigned occupation; // 0 => empty, 1 => agent, 2 => bite
};
typedef std::vector<Field> State;
typedef std::vector<std::vector<double> > MatrixDouble;

class QLearning
{
public:
    QLearning(const unsigned &arenaSizeX, const unsigned &arenaSizeY, const State &initialState, const double &initialValue);


private:
    State state;
    double value;

    MatrixDouble stateActions;


};

#endif // QLEARNING_H
