#include "Player.h"

Player::Player(){

}

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    rowNums = thisGMRef->getBoardSizeX(); 
    colNums = thisGMRef->getBoardSizeY(); 
    
}

Player::~Player()
{
    // delete any heap members here
}
objPosArrayList Player::getPlayerArrayList() const{
    return player; 
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return player.getHeadElement();  
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    if(mainGameMechsRef->getInput() != 0)  // if not null 
    {
        switch(mainGameMechsRef->getInput())
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
        mainGameMechsRef->clearInput();
    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
     
    switch(myDir){ 
        case DOWN:
            getPlayerPos().pos->x ++;  
            break;
        case UP:
            getPlayerPos().pos->x --; 
            break; 
        case LEFT:
            getPlayerPos().pos->y --; 
            break;
        case RIGHT:
            getPlayerPos().pos->y ++; 
            break;
        default:
            break; 
    }
    // wraparound feature
    if(getPlayerPos().pos->x > rowNums-2){
        getPlayerPos().pos->x = 1; 
    }
    if(getPlayerPos().pos->x < 1){
        getPlayerPos().pos->x = rowNums-2;
    }
    if(getPlayerPos().pos->y > colNums-2){
        getPlayerPos().pos->y = 1;
    }
    if(getPlayerPos().pos->y < 1){
        getPlayerPos().pos->y = colNums-2; 
    }
}

// More methods to be added