#pragma once

#include <stdexcept>
#include "Node.h"

class Board
{
public:
    Board();
    Board(int);
    ~Board();

#pragma region Generic array-like functions
private:
    Node* head;
    int n;
    Node* nodeAt(int index);
    Node* tail;
public:
    void add(int);
    int indexOf(int);
    int size;
    void swap(int, int);
    int valueAt(int);
#pragma endregion Generic array-like functions

#pragma region Specific functions
public:
    int gapIndex;
    bool isFinished();
    bool isSolvable();
    void shuffle();
#pragma endregion Specific functions
};
