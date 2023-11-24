#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {rest, up, right, down, left};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        void getPlayerPos(objPos &returnPos); // Upgrade this in iteration 3.
        int getPlayerDir();
        void updatePlayerDir();
        void movePlayer();
        void growPlayer(objPos lastpos);
        void printSnake();

    private:
        enum Dir curr;
        objPos playerPos;   // Upgrade this in iteration 3.

        objPos* check = new objPos;
        objPosArrayList* p_list = new objPosArrayList;

        // Need a reference to the Main Game Mechanisms
        
        GameMechs* mainGameMechsRef;
};

#endif