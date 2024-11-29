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
    // both exitFlag and loseFlag have to be false to run program
    while(!g->getExitFlagStatus() && !g->getLoseFlagStatus() && !g->getWinFlagStatus())  
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
    g = new GameMechs(15, 30); 
    f = new Food(); 
    p = new Player(g,f); 
    p->getFoodlist()->generateFood(*p->getPlayerPos(), g->getBoardSizeX(), g->getBoardSizeY());  
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
    // Main drawing loop draws the board
    char board[g->getBoardSizeX()][g->getBoardSizeY()]; 
    for(int i = 0; i < g->getBoardSizeX(); i++){ // x
        for(int j = 0; j < g->getBoardSizeY(); j++){ // y
            // First are the borders and white spaces
            if((i == 0 || i == g->getBoardSizeX()-1 || j == 0 || j == g->getBoardSizeY()-1))
            {
                board[i][j] = '#';
            }
            else
            {
                board[i][j] = ' '; 
            }

            // Draws the player      
            for(int k = 0; k < (p->getPlayerPos())->getSize(); k++)
            {
                if(i == (p->getPlayerPos())->getElement(k).pos->x && j == (p->getPlayerPos())->getElement(k).pos->y){
                    board[i][j] = (p->getPlayerPos())->getElement(k).symbol; 
                }
            }
            
            // Draws the food
            for(int k = 0; k < FOOD_SPAWN_CAP; k++){
                if(i == p->getFoodlist()->getFoodpos(k).pos->x && j == p->getFoodlist()->getFoodpos(k).pos->y){
                    // Checks for special food and oscilates it
                    if(k==3 && p->getFoodlist()->specialfoodcheck())
                    {
                        if(p->getFoodlist()->getfoodoscillator())
                        {
                            board[i][j]=p->getFoodlist()->getspecial();
                            p->getFoodlist()->switchoscillator();
                        }
                        else
                        {
                            board[i][j]=p->getFoodlist()->getnormal();
                            p->getFoodlist()->switchoscillator();
                        }
                    }
                    // draws non special food
                    else
                    {
                        board[i][j]=p->getFoodlist()->getFoodpos(k).getSymbol();
                    }
                }
            }
            MacUILib_printf("%c", board[i][j]); 
        }
        MacUILib_printf("\n"); 
    }  
    // Game play instructions
    if(!g->getLoseFlagStatus() && !g->getExitFlagStatus() && !g->getWinFlagStatus()){
        MacUILib_printf("Score: %d\n", g->getScore()); 
        MacUILib_printf("Use the 'a', 'w', 's', and 'd', keys to move around the board! \n");
        MacUILib_printf("Food 'o' is worth 1 point\n"); 
        MacUILib_printf("Look for blinking food for 5 points\n");  
    }
    // message if you lose
    else if(g->getLoseFlagStatus()){
        MacUILib_printf("Game Over! You lost, your final score is: %d", g->getScore()); 
    }
    // message if you quit
    else if(g->getExitFlagStatus()){
        MacUILib_printf("Why'd you stop? huh?"); 
    }
    // message if you win
    else if(g->getWinFlagStatus()){
        MacUILib_printf("Congrats, you win the game!\n");
        MacUILib_printf("Your final score is: %d", g->getScore()); 
    }

     
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST/p->getSpeed());
}


void CleanUp(void)
{
    delete g; 
    delete f;
    delete p;  
    MacUILib_uninit();
}
