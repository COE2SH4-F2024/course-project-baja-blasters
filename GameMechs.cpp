#include "GameMechs.h"

GameMechs::GameMechs()
{
    boardSizeX = 30; 
    boardSizeY = 15; 
    //initialize everything else to null; 
    input = 0; 
    exitFlag = false; 
    loseFlag = false; 
    score = 0; 
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX; 
    boardSizeY = boardY; 
    //initialize everything else to null; 
    input = 0; 
    exitFlag = false; 
    loseFlag = false; 
    score = 0; 
}

GameMechs& GameMechs:: operator=(const GameMechs&game)
{
    if(this!=&game)
    {
        this->boardSizeX = game.boardSizeX; 
        this->boardSizeY = game.boardSizeY; 
        this->input = game.input; 
        this->exitFlag = game.exitFlag; 
        this->loseFlag = game.loseFlag; 
        this->score = game.score; 
    }
    return *this;
}


GameMechs::GameMechs(const GameMechs&game)
{
    boardSizeX = game.boardSizeX; 
    boardSizeY = game.boardSizeY; 
    input = game.input; 
    exitFlag = game.exitFlag; 
    loseFlag = game.loseFlag; 
    score = game.score; 
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

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

// More methods should be added here