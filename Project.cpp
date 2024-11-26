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
    // for(int i = 0; i < FOOD_SPAWN_CAP; i++){
    //     f.generateFood(p.getPlayerPos()); 
    // }
    f.generateFood(p.getPlayerPos(), g->getBoardSizeX(), g->getBoardSizeY()); 
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
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    char board[g->getBoardSizeX()][g->getBoardSizeY()]; 
    for(int i = 0; i < g->getBoardSizeX(); i++){ // x
        for(int j = 0; j < g->getBoardSizeY(); j++){ // y
            if (i == p.getPlayerPos().pos->x && j == p.getPlayerPos().pos->y){
                board[i][j] = p.getPlayerPos().symbol;  
            }
            else if((i == 0 || i == g->getBoardSizeX()-1 || j == 0 || j == g->getBoardSizeY()-1)){
                board[i][j] = '#'; 
            }
            else{
                board[i][j] = ' '; 
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
    MacUILib_printf("%d, %d, %c\n", p.getPlayerPos().pos->x, p.getPlayerPos().pos->y, p.getPlayerPos().symbol); 
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
