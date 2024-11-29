#include "GameMechs.h"

// Constructor
GameMechs::GameMechs()
{
    boardSizeX = 30; 
    boardSizeY = 15; 
    input = 0; 
    exitFlag = false; 
    loseFlag = false; 
    winFlag = false; 
    score = 0; 
}

// Also a constructor
GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX; 
    boardSizeY = boardY;  
    input = 0; 
    exitFlag = false; 
    loseFlag = false; 
    winFlag = false; 
    score = 0; 
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

// Copy
GameMechs::GameMechs(const GameMechs &game)
{
    boardSizeX = game.getBoardSizeX(); 
    boardSizeY = game.getBoardSizeY(); 
    input = 0; 
    exitFlag = false; 
    loseFlag = false; 
    winFlag = false; 
    score = 0;
}

// Copy assignment
GameMechs& GameMechs::operator=(const GameMechs &game)
{
    if (this!=&game)
    {
        this->boardSizeX = game.getBoardSizeX(); 
        this->boardSizeY = game.getBoardSizeY(); 
        this->input = 0; 
        this->exitFlag = false; 
        this->loseFlag = false; 
        this->winFlag = false; 
        this->score = 0; 
    }
    return *this;
}

// The ones below are self explanatory
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag; 
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag; 
}   
    

char GameMechs::getInput() const
{
    return input;  
}

int GameMechs::getScore() const
{
    return score; 
}

void GameMechs::incrementScore(int points)
{
    score+=points; 
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX; 
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY; 
}


void GameMechs::setExitTrue()
{
    exitFlag = true; 
}

void GameMechs::setLoseFlag()
{
    loseFlag = true; 
}

void GameMechs::setInput(char this_input)
{
    input = this_input; 
}

void GameMechs::clearInput()
{
    input = 0; 
}

bool GameMechs::getWinFlagStatus() const{
    return winFlag; 
}

void GameMechs::setWinFlag(){
    winFlag = true; 
}