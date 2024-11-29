#include "Player.h"
#include <time.h> 

Player::Player(){
    

}

Player::Player(GameMechs* thisGMRef,Food*thisFood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    foodlist=thisFood;
    rowNums = thisGMRef->getBoardSizeX(); 
    colNums = thisGMRef->getBoardSizeY(); 
    player = new objPosArrayList();
    headsymbol = '@';
    bodysymbol = '+';
    (*player).insertHead(objPos(5, 5, headsymbol));
    speed = 1; 
       
}

Player::~Player()
{
    delete player;
}

Player::Player(const Player &pp)
{
    mainGameMechsRef=pp.mainGameMechsRef;
    foodlist = pp.foodlist;
    myDir = STOP;
    rowNums = mainGameMechsRef->getBoardSizeX(); 
    colNums = mainGameMechsRef->getBoardSizeY(); 
    player = new objPosArrayList();
    headsymbol = pp.headsymbol;
    bodysymbol = pp.bodysymbol;
    (*player).insertHead(objPos(5, 5, headsymbol));
    speed = 1; 
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
        delete this->player; 
        this->player = new objPosArrayList();
        this->getPlayerPos()->insertHead(objPos(5, 5, headsymbol));
        this->headsymbol = pp.headsymbol;
        this->bodysymbol = pp.bodysymbol;
        this->speed = pp.speed; 
    }
    return *this;
    
}
objPosArrayList* Player::getPlayerPos() const
{
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
    (*getPlayerPos()).removeHead();
    (*getPlayerPos()).insertHead(objPos(x,y,bodysymbol));
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
    (*getPlayerPos()).insertHead(objPos(x,y,headsymbol));
    increasePlayerlength();
    // collision check
    if (checkselfcollision())
    {
        mainGameMechsRef->setLoseFlag();
    }
    
    
}

// More methods to be added

Food* Player:: getFoodlist() const
{
    return foodlist;
}

bool Player::checkFoodconsumption()
{
    bool foodeatenflag;
    for(int k = 0; k < FOOD_SPAWN_CAP; k++)
    {
        // as long a player x != food x or player y != food y coordinates: 
        // food is not eaten
        if(((getPlayerPos())->getHeadElement()).pos->x!=getFoodlist()->getFoodpos(k).pos->x || ((getPlayerPos())->getHeadElement()).pos->y!=getFoodlist()->getFoodpos(k).pos->y)
        {
            foodeatenflag = false;
        }
        else
        {
            foodeatenflag=true;
            break;
        }
    }
    return foodeatenflag;
}

void Player::increasePlayerlength()
{
    // srand is for speed
    srand(time(NULL)); 
    if(checkFoodconsumption())
    {
        char collidedFruitSym = getFoodlist()->getFoodpos(player->getHeadElement().pos->x,player->getHeadElement().pos->y).getSymbol();

        // normal food increments score by 1
        if (collidedFruitSym=='o')
        {
            mainGameMechsRef->incrementScore(1);
        }
        // special food increments score by 5 and randomly generates new speed
        else if (collidedFruitSym=='O')
        {
            mainGameMechsRef->incrementScore(5);
            speed = rand() % 5 + 1; 
        }
        
        getFoodlist()->generateFood(*getPlayerPos(), mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());
    }
    else
    {
        (getPlayerPos())->removeTail();
    }
}

bool Player::checkselfcollision()
{
    if (player->getSize()>1)
    {
        int Playerx=player->getHeadElement().pos->x;
        int Playery=player->getHeadElement().pos->y;
        // collision check for the body of the snake 
        for (int i = 1; i < player->getSize(); i++)
        {
            int Pbodyx=player->getElement(i).pos->x;
            int Pbodyy=player->getElement(i).pos->y;
            if (Playerx==Pbodyx && Playery==Pbodyy)
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}

int Player::getSpeed(){
    return speed; 
}

void Player::setSpeed(int s){
    speed = s; 
}