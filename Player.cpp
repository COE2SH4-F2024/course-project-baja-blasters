#include "Player.h"

Player::Player(){

}

Player::Player(GameMechs* thisGMRef,Food*thisFood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    foodlist=thisFood;
    // more actions to be included
    rowNums = thisGMRef->getBoardSizeX(); 
    colNums = thisGMRef->getBoardSizeY(); 
    player = new objPosArrayList();
    (*player).insertHead(objPos(5, 5, '*')); 
    
}

Player::~Player()
{
    // delete any heap members here
}

Player::Player(const Player &pp)
{
    mainGameMechsRef=pp.mainGameMechsRef;
    foodlist = pp.foodlist;
    myDir = STOP;
    rowNums = mainGameMechsRef->getBoardSizeX(); 
    colNums = mainGameMechsRef->getBoardSizeY(); 
    player = new objPosArrayList();
    (*player).insertHead(objPos(5, 5, '*'));
}
Player& Player ::operator=(const Player&pp)
{
    if (this!=&pp)
    {
        this->mainGameMechsRef=pp.mainGameMechsRef;
        this->foodlist=pp.foodlist;
        this->myDir = STOP;
        this->rowNums = mainGameMechsRef->getBoardSizeX(); 
        this->colNums = mainGameMechsRef->getBoardSizeY(); 
        this->player = new objPosArrayList();
        (*this->player).insertHead(objPos(5, 5, '*'));
    }
    return *this;
    
}
objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    

    return player;  
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
    int x = (*getPlayerPos()).getHeadElement().pos->x;
    int y = (*getPlayerPos()).getHeadElement().pos->y;
    switch(myDir){ 
        case DOWN:
             x++;  
            break;
        case UP:
            x --; 
            break; 
        case LEFT:
            y --; 
            break;
        case RIGHT:
            y ++; 
            break;
        default:
            break; 
    }
    
    // wraparound feature
    if(x > rowNums-2){
        x = 1; 
    }
    if(x < 1){
        x = rowNums-2;
    }
    if(y > colNums-2){
        y = 1;
    }
    if(y < 1){
        y = colNums-2; 
    }
    (*getPlayerPos()).insertHead(objPos(x,y,(*getPlayerPos()).getHeadElement().symbol));
}

// More methods to be added

Food* Player:: getFoodlist() const
{
    return foodlist;
}