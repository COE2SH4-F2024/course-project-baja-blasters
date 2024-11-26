#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos = objPos(5, 5, '*'); 
    rowNums = thisGMRef->getBoardSizeX(); 
    colNums = thisGMRef->getBoardSizeY(); 
    
    
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos.getObjPos();  
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    input = mainGameMechsRef->getInput(); 
    if(input != 0)  // if not null 
    {
        switch(input)
        {                      
            case 32:  // exit
                mainGameMechsRef->setExitTrue(); 
                break;
            case 'w': //w
                if(myDir != DOWN){
                    myDir = UP; 
                }
                break; 
            case 'a': //a
                if(myDir != RIGHT){
                    myDir = LEFT; 
                }
                break; 
            case 's': //s 
                if(myDir != UP){
                    myDir = DOWN; 
                }
                break; 
            case 'd': //d
                if(myDir != LEFT){
                    myDir = RIGHT; 
                }
                break; 

            default:
                break;
        }
        input = 0;
    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
     
    switch(myDir){ 
        case DOWN:
            playerPos.pos->x ++;  
            break;
        case UP:
            playerPos.pos->x --; 
            break; 
        case LEFT:
            playerPos.pos->y --; 
            break;
        case RIGHT:
            playerPos.pos->y ++; 
            break;
        default:
            break; 
    }
    // wraparound feature
    if(playerPos.pos->x > rowNums-2){
        playerPos.pos->x = 1; 
    }
    if(playerPos.pos->x < 1){
        playerPos.pos->x = rowNums-2;
    }
    if(playerPos.pos->y > colNums-2){
        playerPos.pos->y = 1;
    }
    if(playerPos.pos->y < 1){
        playerPos.pos->y = colNums-2; 
    }
}

// More methods to be added