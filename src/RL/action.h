#ifndef ACTION_H
#define ACTION_H


class Action
{
public:
    // Each action can be performed; returns reward
    virtual double perform() = 0;
};

#endif // ACTION_H
