#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        bool winFlag; 
        int score;

        int boardSizeX;
        int boardSizeY;


        objPos food;

    public:
        // Rule of 6 stuff
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();
        GameMechs(const GameMechs &game);
        GameMechs& operator=(const GameMechs &game);

        // All rather self explanatory
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();
        bool getWinFlagStatus() const; 
        void setWinFlag(); 

        char getInput() const;
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore(int points);
        
};

#endif