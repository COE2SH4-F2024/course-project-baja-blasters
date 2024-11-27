#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* g; 
Player p; 
//objPosArrayList p.getPlayerArrayList();
Food* f; 

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    while(g->getExitFlagStatus() == false)  
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
    MacUILib_init();
    MacUILib_clearScreen();
    g = new GameMechs(10, 20); 
    f = new Food;
    p = Player(g,f);
    for(int i = 0; i < 5; i++){
        (*f).generateFood((p.getPlayerPos())->getHeadElement(), g->getBoardSizeX(),g->getBoardSizeY()); 
    }//What is this for??
    (*f).generateFood((p.getPlayerPos())->getHeadElement(), g->getBoardSizeX(), g->getBoardSizeY());  
}

void GetInput(void)
{
    if(MacUILib_hasChar()){
        g->setInput(MacUILib_getChar()); 
        p.updatePlayerDir();
        g->clearInput(); 
    }
}

void RunLogic(void)
{
    p.movePlayer();
    p.increasePlayerLength();
    
    /*bool foodeatenflag=false;
    for(int k = 0; k < FOOD_SPAWN_CAP; k++)
    {
        if(((p.getPlayerPos())->getHeadElement()).pos->x!=(*f).getFoodpos(k).pos->x || ((p.getPlayerPos())->getHeadElement()).pos->y!=(*f).getFoodpos(k).pos->y)
        {
            foodeatenflag = false;
        }
        else
        {
            foodeatenflag=true;
            break;
        }
    }
    if(foodeatenflag)
    {
        (*f).generateFood((p.getPlayerPos())->getHeadElement(), g->getBoardSizeX(), g->getBoardSizeY());
    }
    else
    {
        (p.getPlayerPos())->removeTail();
    }*/

}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    char board[g->getBoardSizeX()][g->getBoardSizeY()]; 
    for(int i = 0; i < g->getBoardSizeX(); i++){ // x
        for(int j = 0; j < g->getBoardSizeY(); j++){ // y
            if((i == 0 || i == g->getBoardSizeX()-1 || j == 0 || j == g->getBoardSizeY()-1))
            {
                board[i][j] = '#';
            }
            else
            {
                board[i][j] = ' '; 
            }
       
            for(int k = 0; k < (p.getPlayerPos())->getSize(); k++)
            {
                if(i == (p.getPlayerPos())->getElement(k).pos->x && j == (p.getPlayerPos())->getElement(k).pos->y){
                    board[i][j] = (p.getPlayerPos())->getElement(k).symbol; 
                }
            }
            
            
            for(int k = 0; k < FOOD_SPAWN_CAP; k++){
                if(i == (*f).getFoodpos(k).pos->x && j == (*f).getFoodpos(k).pos->y){
                    board[i][j] = (*f).getFoodpos(k).symbol; 
                }
            }
            MacUILib_printf("%c", board[i][j]); 
        }
        MacUILib_printf("\n"); 
    }  
    MacUILib_printf("%d, %d, %c\n", ((p.getPlayerPos())->getHeadElement()).pos->x, ((p.getPlayerPos())->getHeadElement()).pos->y, ((p.getPlayerPos())->getHeadElement()).symbol); 
    for(int i = 0; i < FOOD_SPAWN_CAP; i++){
        MacUILib_printf("%d, %d, %c\n", (*f).getFoodpos(i).pos->x, (*f).getFoodpos(i).pos->y, (*f).getFoodpos(i).symbol); 
    }

     
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete g; 
    delete f;
    //MacUILib_clearScreen();    

    MacUILib_uninit();
}
