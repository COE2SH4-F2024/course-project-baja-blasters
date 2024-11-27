#include "Player.h"

Player::Player()
{
    mainGameMechsRef = new GameMechs();
    myDir = STOP;

    mainFoodlist = new Food;
    // more actions to be included
    rowNums = mainGameMechsRef->getBoardSizeX(); 
    colNums = mainGameMechsRef->getBoardSizeY(); 
    player = new objPosArrayList();
    (*player).insertHead(objPos(5, 5, 'D'));
}

Player::Player(GameMechs* thisGMRef, Food* thisfood)
{
    mainGameMechsRef=new GameMechs;
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    mainFoodlist=new Food;
    mainFoodlist = thisfood;
    // more actions to be included
    rowNums = thisGMRef->getBoardSizeX(); 
    colNums = thisGMRef->getBoardSizeY(); 
    player = new objPosArrayList();
    (*player).insertHead(objPos(5, 5, 'D')); 

    
}

Player::Player(const Player& playa)
{
    mainGameMechsRef=new GameMechs(*playa.mainGameMechsRef);
    myDir = STOP;

    mainFoodlist=new Food(*playa.mainFoodlist);
    // more actions to be included
    rowNums = playa.mainGameMechsRef->getBoardSizeX(); 
    colNums = playa.mainGameMechsRef->getBoardSizeY(); 
    player = new objPosArrayList();
    (*player).insertHead(objPos(5, 5, 'D'));
}

Player& Player::operator=(const Player&playa)
{
    if (this!=&playa)
    {
        this->mainGameMechsRef=new GameMechs(*playa.mainGameMechsRef);
        this->myDir = STOP;

        this->mainFoodlist=new Food(*playa.mainFoodlist);
        // more actions to be included
        this->rowNums = playa.mainGameMechsRef->getBoardSizeX(); 
        this->colNums = playa.mainGameMechsRef->getBoardSizeY(); 
        this->player = new objPosArrayList();
        (*(this->player)).insertHead(objPos(5, 5, 'D'));
    }
    return *this;
}
Player::~Player()
{
    // delete any heap members here
    delete player;
    delete mainGameMechsRef;
    delete mainFoodlist;
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
    increasePlayerLength();
}

// More methods to be added

bool Player::checkFoodconsumption()
{
    for (int i = 0; i < mainFoodlist->getBinsize(); i++)
    {
        if((*getPlayerPos()).getHeadElement().pos->x==mainFoodlist->getFoodpos(i).pos->x
        && (*getPlayerPos()).getHeadElement().pos->y==mainFoodlist->getFoodpos(i).pos->y)
        {
            return true;
        }
    }
    return false;
}
void Player::increasePlayerLength()
{
    if (checkFoodconsumption())
    {
        mainFoodlist->generateFood((*getPlayerPos()).getHeadElement(),rowNums,colNums);
    }
    else
    {
        (*getPlayerPos()).removeTail();
    }
}