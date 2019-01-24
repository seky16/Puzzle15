#include "pch.h"
#include "Board.h"

Board::Board()
{
    head = tail = nullptr;
    n = size = gapIndex = 0;
    Board(4);
}

Board::Board(int n = 4)
{
    head = tail = nullptr;
    size = gapIndex = 0;
    Board::n = n;

    for (int i = 0; i < n*n; i++)
        add(i);
}

Board::~Board()
{
}

#pragma region Generic array-like functions

Node* Board::nodeAt(int index)
{
    if (index < 0 || index >= size)
        throw std::invalid_argument("Index out of range.");
    Node *out = head;
    for (int i = 0; i < index; i++)
        out = out->next;
    return out;
}

void Board::add(int value)
{
    Node *temp = new Node(value);
    if (head == nullptr)
        tail = head = temp;
    else
    {
        tail->next = temp;
        tail = temp;
    }
    size++;
}

int Board::indexOf(int value)
{
    for (int i = 0; i < size; i++)
        if (valueAt(i) == value)
            return i;
    throw std::invalid_argument("Value not found.");
}

void Board::swap(int first, int second)
{
    Node *firstNode = nodeAt(first);
    Node *secondNode = nodeAt(second);

    int temp = firstNode->value;
    firstNode->value = secondNode->value;
    secondNode->value = temp;

    if (firstNode->value == 0)
        gapIndex = first;
    else if (secondNode->value == 0)
        gapIndex = second;
}

int Board::valueAt(int index)
{
    return nodeAt(index)->value;
}

#pragma endregion Generic array-like functions

#pragma region Specific functions
bool Board::isFinished()
{
    if (valueAt(size - 1) != 0)
        return false; // gap not in last position

    for (int i = 0; i < size - 1; i++)
        if (valueAt(i) != i + 1)
            return false; // invalid position

    return true;
}

bool Board::isSolvable()
{
    // https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html

    // get number of inversions
    int invCount = 0;
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (valueAt(j) != 0 && valueAt(i) > valueAt(j))
                invCount++;

    if (n % 2 == 0) // even grid
    {
        int fromBottom = n - (gapIndex / n);
        if (fromBottom % 2 != 0) // blank on odd row from bottom
            return invCount % 2 == 0;
        else // blank on even row from bottom
            return invCount % 2 != 0;
    }
    else // odd grid
        return invCount % 2 == 0;
}

void Board::shuffle()
{
    // Knuth/Fisher-Yates shuffle
    for (int i = size - 1; i > 0; i--)
    {
        int r = floor(rand() % i);
        swap(i, r);
    }
}
#pragma endregion Specific functions