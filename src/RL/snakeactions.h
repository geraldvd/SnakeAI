#ifndef SNAKEACTIONS_H
#define SNAKEACTIONS_H

// Include project files
#include "snakeengine.h"
#include "action.h"

class SnakeAction : public Action {
public:
    SnakeAction(SnakeEngine *g);
    virtual std::pair<double, std::vector<double> > perform() = 0;

protected:
    // Pointer to the snake instance currently played
    SnakeEngine *game;
};

class ActionUp : public SnakeAction {
public:
    ActionUp(SnakeEngine *g) : SnakeAction(g) {}
    virtual std::pair<double, std::vector<double> > perform();
};

class ActionDown : public SnakeAction {
public:
    ActionDown(SnakeEngine *g) : SnakeAction(g) {}
    virtual std::pair<double, std::vector<double> > perform();
};

class ActionLeft : public SnakeAction {
public:
    ActionLeft(SnakeEngine *g) : SnakeAction(g) {}
    virtual std::pair<double, std::vector<double> > perform();
};

class ActionRight : public SnakeAction {
public:
    ActionRight(SnakeEngine *g) : SnakeAction(g) {}
    virtual std::pair<double, std::vector<double> > perform();
};

#endif // SNAKEACTIONS_H
