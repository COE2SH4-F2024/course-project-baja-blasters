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
Food f; 

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
    p = Player(g); 
    f = Food(); 
    for(int i = 0; i < 5; i++){
        f.generateFood(*p.getPlayerPos(), g->getBoardSizeX(),g->getBoardSizeY()); 
    }
    f.generateFood(*p.getPlayerPos(), g->getBoardSizeX(), g->getBoardSizeY()); 
    //p.getPlayerArrayList().insertHead(objPos(1, 5, 'D')); 
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
    p.getPlayerArrayList().insertHead(*p.getPlayerPos());
    
    bool foodeatenflag=false;
    for(int k = 0; k < FOOD_SPAWN_CAP; k++)
    {
        if((*p.getPlayerPos()).pos->x!=f.getFoodpos(k).pos->x || (*p.getPlayerPos()).pos->y!=f.getFoodpos(k).pos->y)
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
        f.generateFood(*p.getPlayerPos(), g->getBoardSizeX(), g->getBoardSizeY());
    }
    else
    {
        p.getPlayerArrayList().removeTail();
    }

}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    char board[g->getBoardSizeX()][g->getBoardSizeY()]; 
    for(int i = 0; i < g->getBoardSizeX(); i++){ // x
        for(int j = 0; j < g->getBoardSizeY(); j++){ // y
            if((i == 0 || i == g->getBoardSizeX()-1 || j == 0 || j == g->getBoardSizeY()-1)){
                board[i][j] = '#';
            }
            else{
                board[i][j] = ' '; 
            }
            if (p.getPlayerArrayList().getSize()==0)
            {
               if(i == p.getPlayerArrayList().getElement(0).pos->x && j == p.getPlayerArrayList().getElement(0).pos->y){
                    board[i][j] = p.getPlayerArrayList().getElement(0).symbol; 
                } 
            }
            else
            {
                for(int k = 0; k < p.getPlayerArrayList().getSize(); k++){
                    if(i == p.getPlayerArrayList().getElement(k).pos->x && j == p.getPlayerArrayList().getElement(k).pos->y){
                        board[i][j] = p.getPlayerArrayList().getElement(k).symbol; 
                    }
            }
            }
            
            for(int k = 0; k < FOOD_SPAWN_CAP; k++){
                if(i == f.getFoodpos(k).pos->x && j == f.getFoodpos(k).pos->y){
                    board[i][j] = f.getFoodpos(k).symbol; 
                }
            }
            MacUILib_printf("%c", board[i][j]); 
        }
        MacUILib_printf("\n"); 
    }  
    MacUILib_printf("%d, %d, %c\n", (*p.getPlayerPos()).pos->x, (*p.getPlayerPos()).pos->y, (*p.getPlayerPos()).symbol); 
    for(int i = 0; i < FOOD_SPAWN_CAP; i++){
        MacUILib_printf("%d, %d, %c\n", f.getFoodpos(i).pos->x, f.getFoodpos(i).pos->y, f.getFoodpos(i).symbol); 
    }

     
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete g; 
    //MacUILib_clearScreen();    

    MacUILib_uninit();
}
