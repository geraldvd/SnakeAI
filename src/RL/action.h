#ifndef ACTION_H
#define ACTION_H

// Include standard libraries
#include <vector>
#include <utility>


class Action
{
public:
    virtual ~Action() {}
    // Each action can be performed; returns reward and state
    virtual std::pair<double, std::vector<double> > perform() = 0;
};

#endif // ACTION_H
