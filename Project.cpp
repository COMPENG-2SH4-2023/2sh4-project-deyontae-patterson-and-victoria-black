#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* snake;
Player* p;
objPos* pos;
bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}

void Initialize(void)
{
    int x,y;

    MacUILib_init();
    MacUILib_clearScreen();

    MacUILib_printf("Enter Game Board Width (Press 0 to enter default): \n");
    cin >> x;

    MacUILib_printf("\nEnter Game Board Height (Press 0 to enter default): \n");
    cin >> y;

    MacUILib_clearScreen();

    snake = new GameMechs(x,y);

    // snake = new GameMechs();
    p = new Player(snake);
    pos = new objPos();

    p->getPlayerPos(*pos);
    snake->generateFood(*pos);

    snake->clearInput();
    snake->g_delay = DELAY_CONST;
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        snake->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    int i, j;

    for(i=0; i<snake->getBoardSizeY(); i++)
    {
        for(j=0; j<snake->getBoardSizeX(); j++)
        {
            snake->map[i][j] = ' ';
        }
    }

    // Change Direction

    p->updatePlayerDir();
    snake->clearInput();

    // Movement

    p->movePlayer();
    exitFlag = snake->getExitFlagStatus();

    // Inserting the food into the map
    
    for(i=0; i<5; i++)
    {
        snake->food[i].getObjPos(*pos);
        snake->map[pos->y][pos->x] = pos->symbol;
    }

    // Speeding up game

    if(snake->getScore()<10)
    {
        snake->g_delay = 100000;
    }

    else if(snake->getScore()>=10)
    {
        snake->g_delay = 81000;
    }

    else if(snake->getScore()>=20)
    {
        snake->g_delay = 62000;
    }

    else if(snake->getScore()>=30)
    {
        snake->g_delay = 43000;
    }

    else if(snake->getScore()>=40 && snake->getScore()<50)
    {
        snake->g_delay = 24000;
    }

    else
    {
        snake->g_delay = 5000;
    }

}

void DrawScreen(void)
{
    int i, j;
    MacUILib_clearScreen();

    // Top Boarder

    for(i=0; i<snake->getBoardSizeX()+2; i++)
    {
        MacUILib_printf("#");
    }

    MacUILib_printf("\n");

    for(i = 0; i<snake->getBoardSizeY(); i++)
    {
        // Left Boarder

        MacUILib_printf("#");

        // A given row of the map

        for(j = 0; j<snake->getBoardSizeX(); j++)
        {
            MacUILib_printf("%c", snake->map[i][j]);
        }

        // Right Boarder

        MacUILib_printf("#\n");
    }

    // Bottom Boarder

    for(i=0; i<snake->getBoardSizeX()+2; i++)
    {
        MacUILib_printf("#");
    }

    // Player Stats

    MacUILib_printf("\nScore %d\n", snake->getScore());
    MacUILib_printf("======== DEBUG MESSAGE ========\n");
    MacUILib_printf("Board Size: %d X %d\n", snake->getBoardSizeX(), snake->getBoardSizeY());

    MacUILib_printf("Player Direction: ");

    switch(p->getPlayerDir())
    {
    case 1:
        MacUILib_printf("N\n");
        break;

    case 2:
        MacUILib_printf("E\n");
        break;

    case 3:
        MacUILib_printf("S\n");
        break;

    case 4:
        MacUILib_printf("W\n");
        break;

    case 0:
        MacUILib_printf("At Rest\n");
    }

    p->getPlayerPos(*pos);
    MacUILib_printf("Player Position: (%d, %d)\n", pos->x, pos->y);
}

void LoopDelay(void)
{
    MacUILib_Delay(snake->g_delay);
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_printf("Game Ended. You Scored: %d\n", snake->getScore());    
  
    MacUILib_uninit();

    delete snake;
    delete p;
    delete pos;
}
