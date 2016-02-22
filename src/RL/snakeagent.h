#ifndef SNAKEAGENT_H
#define SNAKEAGENT_H

// Include project files
#include <agent.h>

class SnakeAgent : public Agent
{
public:
    SnakeAgent();

    virtual double performAction();
};

#endif // SNAKEAGENT_H
