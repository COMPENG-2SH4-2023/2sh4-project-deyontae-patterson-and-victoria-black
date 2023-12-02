#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    check = new objPos;
    p_list = new objPosArrayList;

    playerPos.x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '@';

    check->x = 0;
    check->y = 0;
    check->symbol = 0;

    p_list->insertHead(playerPos);

    curr = rest;
}

Player::~Player()
{
    // delete any heap members here

    delete check;
    check = nullptr;
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list

    playerPos.getObjPos(returnPos);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    
    
    char move = mainGameMechsRef->getInput();

    switch (move)
    {
    case '\b':
        mainGameMechsRef->setExitTrue();

    case ' ':
        mainGameMechsRef->setExitTrue();
        break;
    
    case 'w':
        if(curr != down)
        {
            curr = up;
        }
        break;

    case 'd':
        if(curr != left)
        {
            curr = right;
        }
        break;

    case 's':
        if(curr != up)
        {
            curr = down;
        }
        break;

    case 'a':
        if(curr != right)
        {
            curr = left;
        }
        break;
    }       

    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    // Collecting the Previous Position of the last member of the Array (will be useful in a second, I promise)

    objPos prev;
    p_list->getTailElement(prev);

    // PPA3 Finite State Machine logic

    switch(curr)
    {
    case up:
        playerPos.y--;

        if(playerPos.y<0)
        {
            playerPos.y = mainGameMechsRef->getBoardSizeY() - 1;
        }

        break;
    
    case down:
        playerPos.y++;

        if(playerPos.y >= mainGameMechsRef->getBoardSizeY())
        {
            playerPos.y = 0;
        }

        break;

    case right:
        playerPos.x++;

        if(playerPos.x >= mainGameMechsRef->getBoardSizeX())
        {
            playerPos.x = 0;
        }

        break;

    case left:
        playerPos.x--;

        if(playerPos.x < 0)
        {
            playerPos.x = mainGameMechsRef->getBoardSizeX() - 1;
        }

        break;
    }

    // Moving shifting the Object List

    p_list->insertHead(playerPos);
    p_list->removeTail();

    // Check if Player has collided with itself or collected food

    checkPlayer(prev);

    // Printing Snake

    printSnake();
}

void Player::checkPlayer(objPos prev)
{
    int i;

    // Checking if The player has collected food

    for(i=0; i<5; i++)
    {
        mainGameMechsRef->getFoodPos(*check, i);

        if(playerPos.isPosEqual(check))
        {
            // PLAYER GROWTH
            
            int j;
            if(check->symbol == 'G')
            {
                for(j=0; j<3; j++)
                {
                    mainGameMechsRef->incrementScore();
                }

                growPlayer(prev);
            }

            else if(check->symbol == 'L')
            {
                for(j=0; j<3; j++)
                {
                    mainGameMechsRef->minusScore();
                }

                if(mainGameMechsRef->getScore()<0)
                {
                    mainGameMechsRef->setLooseTrue();
                }

                growPlayer(prev);
            }

            else if(check->symbol == '-')
            {
                p_list->removeTail();

                if(p_list->getSize()<1)
                {
                    mainGameMechsRef->setLooseTrue();
                }
            }

            else
            {
                mainGameMechsRef->incrementScore();
                growPlayer(prev);
            }

            // FOOD REGENERATION

            mainGameMechsRef->generateFood(playerPos);
            break;
        }
    }

    // Checking if the snake has eaten itself

    for(i=1; i<p_list->getSize(); i++)
    {
        p_list->getElement((*check), i);

        if(playerPos.isPosEqual(check))
        {
            mainGameMechsRef->setLooseTrue();
            break;
        }
    }
}

void Player::growPlayer(objPos lastpos)
{
    p_list->insertTail(lastpos);
}

void Player::printSnake()
{
    int i;

    for(i=0; i<p_list->getSize(); i++)
    {
        p_list->getElement((*check), i);
        mainGameMechsRef->map[check->y][check->x] = check->symbol;
    }
}

int Player::getPlayerDir()
{
    return (int)curr;
}

int Player::snakelen()
{
    return p_list->getSize();
}