#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000
#define row 10
#define col 20

bool exitFlag; 
objPos o; 
GameMechs g; 
Player p; 

char board[row][col]; 


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    while(exitFlag == false)  
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
    o = objPos(); 
    g = GameMechs(row, col); 
    p = Player(&g); 

    exitFlag = false;
}

void GetInput(void)
{
   p.updatePlayerDir(); 
}

void RunLogic(void)
{
    p.movePlayer(); 
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    o = p.getPlayerPos();  

    for(int i = 0; i < row; i++){ // x
        for(int j = 0; j < col; j++){ // y
            if (i == o.pos->x && j == o.pos->y){
                board[i][j] = o.symbol;  
            }
            else if((i == 0 || i == row-1 || j == 0 || j == col-1)){
                board[i][j] = '#'; 
            }
            else{
                board[i][j] = ' '; 
            }
            MacUILib_printf("%c", board[i][j]); 
        }
        MacUILib_printf("\n"); 
    }  
    MacUILib_printf("%d, %d, %c", o.pos->x, o.pos->y, o.symbol); 

     
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
