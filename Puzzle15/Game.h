#pragma once

#include <ctime>
#include <vector>
#include <cmath>
#include <sstream>

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
    bool checkBoardFinished();
    string displayBoard();
    vector<int> Board;
    void makeMove(int move, bool invert);
    void restart();
private:
    int N;
    bool checkBoardSolvable();
    void switchPlaces(int firstIndex, int secondIndex);
    int MovesCount;
    vector<int> StartingBoard;
    int GapIndex;
};
