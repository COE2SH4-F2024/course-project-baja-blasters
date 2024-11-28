#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* g; 
Player* p; 
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
    f = new Food(); 
    p = new Player(g,f); 
    p->getFoodlist()->generateFood()(*p->getPlayerPos(), g->getBoardSizeX(), g->getBoardSizeY());  
}

void GetInput(void)
{
    if(MacUILib_hasChar()){
        g->setInput(MacUILib_getChar()); 
        p->updatePlayerDir();
        g->clearInput(); 
    }
}

void RunLogic(void)
{
    p->movePlayer();
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
       
            for(int k = 0; k < (p->getPlayerPos())->getSize(); k++)
            {
                if(i == (p->getPlayerPos())->getElement(k).pos->x && j == (p->getPlayerPos())->getElement(k).pos->y){
                    board[i][j] = (p->getPlayerPos())->getElement(k).symbol; 
                }
            }
            
            
            for(int k = 0; k < FOOD_SPAWN_CAP; k++){
                if(i == p->getFoodlist()->getFoodpos(k).pos->x && j == p->getFoodlist()->getFoodpos(k).pos->y){
                    board[i][j] = p->getFoodlist()->getFoodpos(k).symbol; 
                }
            }
            MacUILib_printf("%c", board[i][j]); 
        }
        MacUILib_printf("\n"); 
    }  
    //MacUILib_printf("%d, %d, %c\n", ((p->getPlayerPos())->getHeadElement()).pos->x, ((p->getPlayerPos())->getHeadElement()).pos->y, ((p->getPlayerPos())->getHeadElement()).symbol); 
    // for(int i = 0; i < FOOD_SPAWN_CAP; i++){
    //     MacUILib_printf("%d, %d, %c\n", p->getFoodlist()->getFoodpos(i).pos->x, p->getFoodlist()->getFoodpos(i).pos->y, p->getFoodlist()->getFoodpos(i).symbol); 
    // }
    // for(int i = 0; i < p->getPlayerPos()->getSize(); i++){
    //     MacUILib_printf("%d, %d, %c, ", p->getPlayerPos()->getElement(i).pos->x, p->getPlayerPos()->getElement(i).pos->y, p->getPlayerPos()->getElement(i).symbol); 
    //     MacUILib_printf("\n"); 
    // }
    MacUILib_printf("Score: %d", g->getScore()); 

     
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete g; 
    delete f;
    delete p;
    //MacUILib_clearScreen();    

    MacUILib_uninit();
}
