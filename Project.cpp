#include <iostream>
#include <string>
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
char bug[16];

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

void scoreboard(int player_score)
{
    int i;
    int* scores = new int[5];
    char** names = new char*[5];
    FILE* file;

    for(i=0; i<5; i++)
    {
        names[i] = new char[8];
    }

    // Read Names

    file = fopen("names.txt", "r");

    for(i=0; i<5; i++)
    {
        fscanf(file, "%s", names[i]);
    }

    fclose(file);

    // Read Scores

    file = fopen("scores.txt", "r");

    for(i=0; i<5; i++)
    {
        fscanf(file, "%d", &scores[i]);
    }

    fclose(file);

    // Operations

    for(i=0; i<5; i++)
    {
        if(scores[i] < player_score)
        {
            // Insert new name and score into lists.

            int j;

            for(j=4; j>i; j--)
            {
                scores[j] = scores[j-1];
                strcpy(names[j], names[j-1]);
            }

            scores[i] = player_score;

            MacUILib_printf("\nCongratulations!\nYou made it to place %d on the Leaderboard!\n\nEnter your name (8 characters max):\n", (i+1));

            cin >> names[i];

            // Overwrite Names

            file = fopen("names.txt", "w");

            for (j=0; j<5; j++)
            {
                fprintf(file, "%s\n", names[j]);
            }

            fclose(file);

            // Overwrite Scores

            file = fopen("scores.txt", "w");

            for (j=0; j<5; j++)
            {
                fprintf(file, "%d\n", scores[j]);
            }

            fclose(file);

            break;
        }
    }

    // Printing LeaderBoard

    MacUILib_Delay(100000);
    MacUILib_printf("\n\nLEADERBOARD:\n\n");

    for(i=0; i<5; i++)
    {
        MacUILib_Delay(100000);
        MacUILib_printf("%s -----> %d\n", names[i], scores[i]);
    }

    // Free space

    for(int i=0; i<5; i++)
    {
        delete[] names[i];
        names[i] = nullptr;
    }

    delete[] names;
    delete[] scores;
}

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
    // Input Gameboard Size

    int x,y;

    MacUILib_init();
    

    while(!MacUILib_hasChar())
    {        
        MacUILib_clearScreen();
        MacUILib_Delay(500000);

        MacUILib_printf("\t\tHello!\n\t     Welcome to:\n\nDeyontae Patterson and Victoria Black's\n\n\n\t     SNAKE GAME\n\n");
        MacUILib_printf("Press any key to continue...\n");
        MacUILib_Delay(500000);
    }

    MacUILib_clearScreen();

    MacUILib_printf("Enter Game Board Width (Press 0 to enter default): \n");
    cin >> x;

    MacUILib_printf("\nEnter Game Board Height (Press 0 to enter default): \n");
    cin >> y;

    MacUILib_clearScreen();

    // Starting Game

    snake = new GameMechs(x,y);

    // snake = new GameMechs();
    p = new Player(snake);
    pos = new objPos();

    p->getPlayerPos(*pos);
    snake->generateFood(*pos);

    snake->clearInput();
    snake->g_delay = DELAY_CONST;

    // Debug Message

    strcpy(bug, "[Debug Message]");
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
        snake->setInput(MacUILib_getChar());
        
        if((snake->getInput() != 'w') && (snake->getInput() != 'd') && (snake->getInput() != 's') && (snake->getInput() != 'a') && (snake->getInput() != '\b') && (snake->getInput() != ' '))
        {
            strcpy(bug, "Invalid Input!");
        }
        else
        {
            strcpy(bug, "[Debug Message]");
        }
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

    snake->map[0][0] = ' ';

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

    MacUILib_printf("\nScore %d  \tSnake Length: %d\n", snake->getScore(), p->snakelen());
    MacUILib_printf("======== %s ========\n", bug);
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
    scoreboard(snake->getScore());

    MacUILib_Delay(10000000);
  
    MacUILib_uninit();

    delete snake;
    delete p;
    delete pos;
}