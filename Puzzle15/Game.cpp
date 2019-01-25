#include "pch.h"
#include "Game.h"

Game::Game(int n = 4)
{
    // initialize board
    Game::n = n;
    movesCount = 0;
    board = Board(n);

    do
        board.shuffle();
    while (!board.isSolvable() || board.isFinished()); // shuffle until it is solvable or not finished
}

Game::~Game()
{
}

string Game::displayBoard()
{
    stringstream output;
    output << endl << endl;
    for (int i = 0; i < board.size; i++)
    {
        string val = board.valueAt(i) == 0 ? " " : to_string(board.valueAt(i));
        output << "\t" << val;
        if ((i + 1) % n == 0)
        {
            output << endl << endl;
        }
    }
    output << endl;
    output << "Moves: " << movesCount << endl << endl;
    return output.str();
}

bool Game::isFinished()
{
    return board.isFinished();
}

void Game::makeMove(int move, bool invert)
{
    if (invert)
    {
        switch (move)
        {
        case MOVE_UP:
            move = MOVE_DOWN;
            break;
        case MOVE_DOWN:
            move = MOVE_UP;
            break;
        case MOVE_LEFT:
            move = MOVE_RIGHT;
            break;
        case MOVE_RIGHT:
            move = MOVE_LEFT;
            break;
        default:
            return;
        }
    }

    switch (move)
    {
    case MOVE_UP:
        if (board.gapIndex >= (n * (n - 1)))
            return; // illegal move
        board.swap(board.gapIndex, board.gapIndex + n);
        break;
    case MOVE_DOWN:
        if (board.gapIndex < n)
            return; // illegal move
        board.swap(board.gapIndex, board.gapIndex - n);
        break;
    case MOVE_LEFT:
        if (board.gapIndex % n == (n - 1))
            return; // illegal move
        board.swap(board.gapIndex, board.gapIndex + 1);
        break;
    case MOVE_RIGHT:
        if (board.gapIndex % n == 0)
            return; // illegal move
        board.swap(board.gapIndex, board.gapIndex - 1);
        break;
    default:
        return;
    }
    movesCount++;
}