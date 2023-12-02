#include "GameMechs.h"

GameMechs::GameMechs()
{
    int i,j;

    exitFlag = false;
    clearInput();

    boardSizeX = 30;
    boardSizeY = 15;

    score = 0;

    map = new char*[boardSizeY];

    for(i = 0; i<boardSizeY; i++)
    {
        map[i] = new char[boardSizeX];
    }

    for(i=0; i<boardSizeY; i++)
    {
        for(j=0; j<boardSizeX; j++)
        {
            map[i][j] = ' ';
        }
    }
}

GameMechs::GameMechs(int boardX, int boardY)
{
    int i,j;

    exitFlag = false;
    clearInput();

    boardSizeX = (boardX >= 10) ? boardX:30;
    boardSizeY = (boardY >= 5) ? boardY:15;

    score = 0;

    map = new char*[boardSizeY];

    for(i = 0; i<boardSizeY; i++)
    {
        map[i] = new char[boardSizeX];
    }

    for(i=0; i<boardSizeY; i++)
    {
        for(j=0; j<boardSizeX; j++)
        {
            map[i][j] = ' ';
        }
    }
}

// do you need a destructor?

GameMechs::~GameMechs()
{
    int i;

    boardSizeX = 0;
    boardSizeY = 0;

    for(i=0; i<boardSizeY; i++)
    {
        delete[] map[i];
        map[i] = nullptr;
    }

    delete[] map;
    map = nullptr;
}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

bool GameMechs::getLooseFlagStatus()
{
    return looseFlag;
}

void GameMechs::setLooseTrue()
{
    looseFlag = true;
    GameMechs::setExitTrue();
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::minusScore()
{
    score--;
}

void GameMechs::generateFood(objPos blockOff)
{
    int i = 0;
    int j = 0;

    int new_x, new_y;

    int *V_x = new int[boardSizeX];
    int *V_y = new int[boardSizeY];

    for(i=0; i<boardSizeX; i++)
    {
        V_x[i] = 0;
    }

    for(i=0; i<boardSizeY; i++)
    {
        V_y[i] = 0;
    }

    V_x[blockOff.x]++;
    V_y[blockOff.y]++;

    i = 0;

    while(i<5)
    {
        new_x = rand() % boardSizeX;
        new_y = rand() % boardSizeY;

        if(V_x[new_x]==0 || V_y[new_y]==0)
        {
            V_x[new_x]++;
            V_y[new_y]++;

            food[i].x = new_x;
            food[i].y = new_y;
            food[i].symbol = 'O';

            i++;
        }
    }

    food[2].symbol = 'G';
    food[4].symbol = 'L';
    food[1].symbol = '-';

    delete[] V_x;
    delete[] V_y;
}

void GameMechs::getFoodPos(objPos &returnPos, int index)
{
    returnPos.x = food[index].x;
    returnPos.y = food[index].y;
    returnPos.symbol = food[index].symbol;
}
