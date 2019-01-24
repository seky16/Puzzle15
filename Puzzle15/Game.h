#pragma once

#include <sstream>
#include "Board.h"

using namespace std;

enum Move
{
    MOVE_UP = 72,
    MOVE_DOWN = 80,
    MOVE_LEFT = 75,
    MOVE_RIGHT = 77
};

class Game
{
public:
    Game(int n);
    ~Game();
private:
    int n;
    int movesCount;
    Board startingBoard;
public:
    Board board;
    string displayBoard();
    bool isFinished();
    void makeMove(int move, bool invert);
    void restart();
};
