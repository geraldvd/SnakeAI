#ifndef SNAKEACTIONS_H
#define SNAKEACTIONS_H

// Include project files
#include "action.h"

class ActionUp : public Action {
public:
    virtual double perform();
}

#endif // SNAKEACTIONS_H
