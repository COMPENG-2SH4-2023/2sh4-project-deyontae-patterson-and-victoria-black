#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        
        int boardSizeX;
        int boardSizeY;

        bool looseFlag;
        int score;

    public:
        char **map;
        objPos food[5];
        int g_delay;

        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();
        
        bool getExitFlagStatus();
        void setExitTrue();

        void setLooseTrue();
        bool getLooseFlagStatus();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getScore();
        void incrementScore();
        void minusScore();

        int getBoardSizeX();
        int getBoardSizeY();

        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos, int index);
      

};

#endif