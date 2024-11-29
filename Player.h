#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"
#include <iostream>

class Player
{   
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        // constructors
        Player(); 
        Player(GameMechs* thisGMRef,Food*thisFood);
        // destructors
        ~Player();
        // Copy assignment and copy assignment editor
        Player(const Player &pp);
        Player& operator=(const Player&pp);

        // functions to involving the player
        objPosArrayList* getPlayerPos() const;      
        void updatePlayerDir();
        void movePlayer();
        bool checkFoodconsumption(); 
        void increasePlayerlength();
        bool checkselfcollision();
        int getSpeed(); 
        void setSpeed(int s);        

        // functions involving food
        Food* getFoodlist()const;

    private:
        // The player is associated with almost everything. 
        // below is the array list of objPos (coordinates and symbol) of the snake
        objPosArrayList* player;
        char headsymbol;
        char bodysymbol;       
        enum Dir myDir;
        // The food associated with the player
        Food* foodlist;
        // The game mechanics associated with the player
        GameMechs* mainGameMechsRef;
        int rowNums; 
        int colNums; 
        int speed; 

};

#endif