#pragma once

#include "Game.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <conio.h>

using namespace std;

void clear();

int getKeyPress();

int main();

enum AllowedKeys
{
    UP_ARROW = 72,
    DOWN_ARROW = 80,
    LEFT_ARROW = 75,
    RIGHT_ARROW = 77,
    R_KEY = 'r',
    N_KEY = 'n',
    I_KEY = 'i',
    ESC = 27
};