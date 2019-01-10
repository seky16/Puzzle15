#include "pch.h"
#include "Puzzle15.h"

//clears console https://stackoverflow.com/a/52895729
void clear()
{
    if (system(nullptr)) {
#if defined _WIN32
        system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
#elif defined (__APPLE__)
        system("clear");
#endif
    }
}

int getKeyPress()
{
    switch (int c = _getch())
    {
    case UP_ARROW:
    case DOWN_ARROW:
    case LEFT_ARROW:
    case RIGHT_ARROW:
    case R_KEY:
    case N_KEY:
    case I_KEY:
    case ESC:
        return c;
    default:
        return getKeyPress();
    }
}

int main()
{
    srand((unsigned)time(nullptr));

    // program loop
    while (true)
    {
        int n;
        cout << "What size should the puzzle be (NxN)?: ";
        cin >> n;
        while (n <= 1 || n > 9)
        {
            cout << "Enter number between 2 and 9 (inclusive): ";

            // http://www.cs.technion.ac.il/users/yechiel/c++-faq/istream-and-ignore.html
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> n;
        }

        Game game = Game(n);

        bool newGame = false;
        bool invert = false;
        string invertString = "(OFF)";

        // game loop
        while (!game.checkBoardFinished() && !newGame)
        {
            clear();
            cout << game.displayBoard();
            cout << "Use arrow keys to move." << endl;
            cout << "Press I to invert controls. " << invertString << endl;
            cout << "Press R to restart (with same board)." << endl;
            cout << "Press N for a new Game." << endl;
            cout << "Press ESC to exit." << endl;

            int key = getKeyPress();
            switch (key)
            {
            case R_KEY:
                game.restart();
                break;
            case N_KEY:
                clear();
                newGame = true;
                break;
            case I_KEY:
                invert = !invert;
                invertString = invert ? "(ON)" : "(OFF)";
                break;
            case ESC:
                return 0;
            default:
                game.makeMove(key, invert);
                break;
            }
        }

        if (newGame)
            continue;

        clear();
        cout << game.displayBoard();

        cout << "CONGRATULATIONS, YOU WON!";
        cout << endl << endl;
    }

    return 0;
}