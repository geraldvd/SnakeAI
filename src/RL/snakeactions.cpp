#include "snakeactions.h"

SnakeAction::SnakeAction(SnakeEngine *g) :
    game(g)
{

}

std::pair<double, std::vector<double> > ActionUp::perform()
{
    double reward = this->game->step(UP);
    std::vector<double> newState = this->game->getStateVector();

    return std::pair<double,std::vector<double> >(reward, newState);
}

std::pair<double, std::vector<double> > ActionDown::perform()
{
    double reward = this->game->step(DOWN);
    std::vector<double> newState = this->game->getStateVector();

    return std::pair<double,std::vector<double> >(reward, newState);
}


std::pair<double, std::vector<double> > ActionLeft::perform()
{
    double reward = this->game->step(LEFT);
    std::vector<double> newState = this->game->getStateVector();

    return std::pair<double,std::vector<double> >(reward, newState);
}


std::pair<double, std::vector<double> > ActionRight::perform()
{
    double reward = this->game->step(RIGHT);
    std::vector<double> newState = this->game->getStateVector();

    return std::pair<double,std::vector<double> >(reward, newState);
}
