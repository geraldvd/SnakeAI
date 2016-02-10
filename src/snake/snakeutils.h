#ifndef SNAKEUTILS_H
#define SNAKEUTILS_H

enum Direction {
    NONE=0, UP=-1, DOWN=1, LEFT=-2, RIGHT=2
};

struct BlockState {
    unsigned x;
    unsigned y;
    Direction currentDirection;
    bool isHead;
};


#endif // SNAKEUTILS_H

