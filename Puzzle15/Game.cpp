#include "pch.h"
#include "Game.h"

Game::Game(int n = 4)
{
    // initialize board
    N = n;
    MovesCount = 0;
    int size = n * n;
    Board = vector<int>(size);
    for (int i = 0; i < size; i++)
    {
        Board[i] = i;
    }
    /*/
    Board.erase(Board.begin());
    Board.push_back(0);
    switchPlaces(Board.size() - 2, Board.size() - 1); // solvable
    switchPlaces(Board.size() - 2, Board.size() - 3); // unsolvable
    bool test = checkBoardSolveable();//*/

    //
    do
    {
        // shuffle the board (Knuth-fisher-Yates shuffle)
        for (int i = size - 1; i > 0; i--)
        {
            int r = floor(rand() % i);

            switchPlaces(i, r);
        }
        // until it is solvable
    } while (!checkBoardSolvable());//*/

    StartingBoard = Board;
}

Game::~Game()
{
}

bool Game::checkBoardSolvable()
{
    // https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html

    // get number of inversions
    int invCount = 0;
    for (int i = 0; i < Board.size(); i++)
    {
        for (int j = i + 1; j < Board.size(); j++)
        {
            if (Board[j] != 0 && Board[i] > Board[j])
                invCount++;
        }

        if (Board[i] == 0)
            GapIndex = i;
    }

    // even grid
    if (N % 2 == 0)
    {
        int fromBottom = N - (GapIndex / N);
        // blank on odd row from bottom
        if (fromBottom % 2 != 0)
        {
            return invCount % 2 == 0;
        }
        else // blank on even row; counting from bottom
        {
            return invCount % 2 != 0;
        }
    }
    else // odd grid
    {
        return invCount % 2 == 0;
    }
}

void Game::switchPlaces(int firstIndex, int secondIndex)
{
    int temp = Board[firstIndex];
    Board[firstIndex] = Board[secondIndex];
    Board[secondIndex] = temp;


    if (Board[firstIndex] == 0)
        GapIndex = firstIndex;
    else if (Board[secondIndex] == 0)
        GapIndex = secondIndex;
}

bool Game::checkBoardFinished()
{
    if (Board.back() != 0)
        return false;

    for (int i = 0; i < Board.size() - 1; i++)
    {
        if (Board[i] != i + 1)
            return false;
    }

    return true;
}

string Game::displayBoard()
{
    stringstream output;
    output << endl << endl;
    for (int i = 0; i < Board.size(); i++)
    {
        string val = Board[i] == 0 ? " " : to_string(Board[i]);
        output << "\t" << val;
        if ((i + 1) % N == 0)
        {
            output << endl << endl;
        }
    }
    output << endl;
    output << "Moves: " << MovesCount << endl << endl;
    return output.str();
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
        if (GapIndex >= (N * (N - 1)))
            return; // illegal move
        switchPlaces(GapIndex, GapIndex + N);
        break;
    case MOVE_DOWN:
        if (GapIndex < N)
            return; // illegal move
        switchPlaces(GapIndex, GapIndex - N);
        break;
    case MOVE_LEFT:
        if (GapIndex % N == (N - 1))
            return; // illegal move
        switchPlaces(GapIndex, GapIndex + 1);
        break;
    case MOVE_RIGHT:
        if (GapIndex % N == 0)
            return; // illegal move
        switchPlaces(GapIndex, GapIndex - 1);
        break;
    default:
        return;
    }
    MovesCount++;
}

void Game::restart()
{
    Board = StartingBoard;
    MovesCount = 0;

    for (int i = 0; i < Board.size(); i++)
    {
        if (Board[i] == 0)
        {
            GapIndex = i;
            break;
        }
    }
}